#include "TcpServer.h"
#include "qlc_log.h"
namespace qlc{
static qlc::Logger::ptr g_logger =QLC_LOG_NAME("system");
static EventLoop* CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        QLC_LOG_FATAL(g_logger)<<"mainloop is null!";
    }
    return loop;
}
TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg, Option option)
        :loop_(CheckLoopNotNull(loop))
        ,ipPort_(listenAddr.toIpPort())
        ,name_(nameArg)
        ,acceptor_(new Acceptor(loop,listenAddr,option==kReusePort))
        ,threadPool_(new EventLoopThreadPool(loop,name_))
        ,connectionCallback_()
        ,messageCallback_()
        ,nextConnId_(1)
        ,started_(0)
{
    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection,
    this,std::placeholders::_1, std::placeholders::_2));

}

TcpServer::~TcpServer()
{
    for(auto &item:connections_){
        TcpConnectionPtr conn(item.second); 
        item.second.reset();//让他置空当参数为空指针时，reset()会释放原来指针所管理的资源，同时将指针置为空。
        //释放所有的连接 也就是说loop里面
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed, conn)
        );
    }
}
void TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}
void TcpServer::start()
{   
    std::cout<<"TcpServer start"<<std::endl;
    if (started_++ == 0) // 防止一个TcpServer对象被start多次
    {
        threadPool_->start(threadInitCallback_); // 启动底层的loop线程池
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));//Acceptor加入到loop 并且进行监听
    }
}
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    //重点内容
    // 轮询算法，选择一个subLoop，来管理channel
    EventLoop *ioLoop = threadPool_->getNextLoop(); 
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);//打印出这个ip地址的第几个连接
    ++nextConnId_;
    std::string connName = name_ + buf;
    QLC_LOG_FMT_INFO(g_logger,"TcpServer::newConnection [%s] - new connection [%s] from %s",
        name_.c_str(), connName.c_str(), peerAddr.toIpPort().c_str());
    // 通过sockfd获取其绑定的本机的ip地址和端口信息
    sockaddr_in local;
    ::bzero(&local, sizeof(local));
    socklen_t addrlen = sizeof(local);
    if (::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0)
    {
        QLC_LOG_ERROR(g_logger)<<"sockets::getLocalAddr";
    }
    InetAddress localAddr(local);
    // 根据连接成功的sockfd，创建TcpConnection连接对象
    TcpConnectionPtr conn(new TcpConnection(
                            ioLoop,
                            connName,
                            sockfd,   // Socket Channel
                            localAddr,
                            peerAddr));
    connections_[connName] = conn;
    // 下面的回调都是用户设置给TcpServer=>TcpConnection=>Channel=>Poller=>notify channel调用回调
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);

    // 设置了如何关闭连接的回调   conn->shutDown()
    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, std::placeholders::_1)
    );

    // 直接调用TcpConnection::connectEstablished
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}
void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->runInLoop(
        std::bind(&TcpServer::removeConnectionInLoop, this, conn)
    );
}
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    QLC_LOG_FMT_INFO(g_logger,"TcpServer::removeConnectionInLoop [%s] - connection %s\n", 
        name_.c_str(), conn->getName().c_str());

    connections_.erase(conn->getName());
    EventLoop *ioLoop = conn->getLoop(); 
    ioLoop->queueInLoop(
        std::bind(&TcpConnection::connectDestroyed, conn)
    );
}
}
