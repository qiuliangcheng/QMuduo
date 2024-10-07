#include "TcpConnection.h"
#include "qlc_log.h"
#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include "channel.h"
namespace qlc{
static qlc::Logger::ptr g_logger=QLC_LOG_NAME("system");
static EventLoop* CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        QLC_LOG_FATAL(g_logger)<<"TcpConnection Loop is null!";
    }
    return loop;
}
TcpConnection::TcpConnection(EventLoop *loop, std::string &name, int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr)
    : loop_(CheckLoopNotNull(loop))
    , name_(name)
    , localAddr_(localAddr)
    , peerAddr_(peerAddr)
    , state_(kConnecting)
    , reading_(true)
    , socket_(new Socket(sockfd))
    , channel_(new Channel(loop, sockfd))
    , highWaterMark_(64*1024*1024) // 64M
{
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleRead, this, std::placeholders::_1)
    );
    channel_->setWriteCallback(
        std::bind(&TcpConnection::handleWrite, this)
    );
    channel_->setCloseCallback(
        std::bind(&TcpConnection::handleClose, this)
    );
    channel_->setErrorCallback(
        std::bind(&TcpConnection::handleError, this)
    );
    QLC_LOG_FMT_INFO(g_logger,"TcpConnection::ctor[%s] at fd=%d\n", name_.c_str(), sockfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    QLC_LOG_FMT_INFO(g_logger,"TcpConnection::dtor[%s] at fd=%d state=%d \n", 
        name_.c_str(), channel_->fd(), (int)state_);
}
void TcpConnection::connectDestroyed()
{
    if (state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll(); // 把channel的所有感兴趣的事件，从poller中del掉
        connectionCallback_(shared_from_this());
    }
    channel_->remove(); // 把channel从poller中删除掉

}
void TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading(); // 向poller注册channel的epollin事件
    // 新连接建立，执行回调
    connectionCallback_(shared_from_this());
}
void TcpConnection::send(const std::string &buf)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf.c_str(), buf.size());//走到这说明这个线程肯定没有阻塞
        }
        else
        {
            loop_->runInLoop(std::bind(
                &TcpConnection::sendInLoop,
                this,
                buf.c_str(),
                buf.size()
            ));
        }
    }
}
/**
 * 发送数据  应用写的快， 而内核发送数据慢， 需要把待发送数据写入缓冲区， 而且设置了水位回调
 */ 
void TcpConnection::sendInLoop(const void *message, size_t len)
{
    ssize_t nwrote = 0;//已经写了的长度
    size_t remaining = len;//剩余的长度
    bool faultError = false;//是否出错了
    // 之前调用过该connection的destoryed，不能再进行发送了
    if (state_ == kDisconnected)
    {
        QLC_LOG_ERROR(g_logger)<<"disconnected, give up writing!";
        return;
    }
    // 表示channel_第一次开始写数据，而且缓冲区没有待发送数据
    if (!channel_->isWriteEvent() && outputBuffer_.readableBytes() == 0){
        //说明之前没有写事件
        nwrote = ::write(channel_->fd(), message, len);
        if (nwrote >= 0){
            remaining = len - nwrote;
            if (remaining == 0 && writeCompleteCallback_)
            {
                // 既然在这里数据全部发送完成，就不用再给channel设置epollout事件了
                loop_->queueInLoop(
                    std::bind(writeCompleteCallback_, shared_from_this())
                );
            }
        }
        else{ //说明发送失败
            nwrote = 0;
            if (errno != EWOULDBLOCK)
            {
                QLC_LOG_ERROR(g_logger)<<"TcpConnection::sendInLoop";
                if (errno == EPIPE || errno == ECONNRESET) // SIGPIPE  RESET
                {
                    faultError = true;
                }
            }
        }
    }
    // 说明当前这一次write，并没有把数据全部发送出去，剩余的数据需要保存到缓冲区当中，然后给channel
    // 注册epollout事件，poller发现tcp的发送缓冲区有空间，会通知相应的sock-channel，调用writeCallback_回调方法
    // 也就是调用TcpConnection::handleWrite方法，把发送缓冲区中的数据全部发送完成
    if (!faultError && remaining > 0) {
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_
            && oldLen < highWaterMark_
            && highWaterMarkCallback_)
        {
            loop_->queueInLoop(
                std::bind(highWaterMarkCallback_, shared_from_this(), oldLen+remaining)
            );
        }//高水位回调函数  就是说我要发送的数据大于某个值 就会触发
        outputBuffer_.append((char*)message + nwrote, remaining);//放到这里面
        if (!channel_->isWriteEvent())
        {
            channel_->enableWriting(); // 这里一定要注册channel的写事件，否则poller不会给channel通知epollout
        }
    }



}
void TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(
            std::bind(&TcpConnection::shutdownInLoop, this)
        );
    }

}
void TcpConnection::handleRead(Timestamp receiveTime)
{
    int savedErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    if (n > 0)
    {
        // 已建立连接的用户，有可读事件发生了，调用用户传入的回调操作onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)
    {
        handleClose();
    }
    else
    {
        errno = savedErrno;
        QLC_LOG_ERROR(g_logger)<<"TcpConnection::handleRead";
        handleError();
    }
}
void TcpConnection::handleWrite()
{
    //channel被监听到就会运行一遍这个函数
    if (channel_->isWriteEvent())
    {
        int savedErrno = 0;
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &savedErrno);
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->disableWriting();
                if (writeCompleteCallback_)
                {
                    // 唤醒loop_对应的thread线程，执行回调
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this())
                    );
                }
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else
        {
            QLC_LOG_ERROR(g_logger)<<"TcpConnection::handleWrite";
        }
    }
    else
    {
        QLC_LOG_FMT_ERROR(g_logger,"TcpConnection fd=%d is down, no more writing \n", channel_->fd());
    }

}
void TcpConnection::handleClose()
{
    QLC_LOG_FMT_INFO(g_logger,"TcpConnection::handleClose fd=%d state=%d \n", channel_->fd(), (int)state_);
    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr); // 执行连接关闭的回调
    closeCallback_(connPtr); // 关闭连接的回调  执行的是TcpServer::removeConnection回调方法
}
void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof(optval);
    int err = 0;
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    QLC_LOG_ERROR(g_logger)<<"TcpConnection::handleError name="<<name_<<"error num="<<err;
}

void TcpConnection::shutdownInLoop()
{
    if (!channel_->isWriteEvent()) // 说明outputBuffer中的数据已经全部发送完成 对写时间不感兴趣
    {
        socket_->shutdownWrite(); // 关闭写端
    }
}
}