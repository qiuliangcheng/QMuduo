#ifndef __QLC_TCPCONNECTION_H
#define __QLC_TCPCONNECTION_H
#include "noncopyable.h"
#include "EventLoop.h"
#include "callback.h"
#include "InetAddress.h"
#include "Buffer.h"
#include <memory>
#include <string>
//这个文件是用来将所读到的 或者所需要写入发送的数据放到一个缓存区里面 因为内核发送数据很慢
//所以我们需要写到buffer  这样才能提高效率
namespace qlc{
class Socket;
class TcpConnection:Noncopyable,public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop* loop,std::string&name,int sockfd,const InetAddress& localAddr,const InetAddress& peerAddr);
    ~TcpConnection();
    EventLoop* getLoop(){return loop_;}
    enum State{
        kDisconnected, 
        kConnecting, 
        kConnected, 
        kDisconnecting
    };//TcpConnect的连接状态
    bool connected() const { return state_ == kConnected; }
    void connectDestroyed();//就是将loop里面的channel删除
    void connectEstablished();
    const InetAddress& localAddress() const { return localAddr_; }
    const InetAddress& peerAddress() const { return peerAddr_; }
    const std::string& getName() const{ return name_;}
    // 发送数据
    void send(const std::string &buf);//服务端发送数据到客户端
    // 关闭连接
    void shutdown();
    void setConnectionCallback(const ConnectionCallback& cb)
    { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback& cb)
    { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    { writeCompleteCallback_ = cb; }
    void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark)
    { highWaterMarkCallback_ = cb; highWaterMark_ = highWaterMark; }
    void setCloseCallback(const CloseCallback& cb)
    { closeCallback_ = cb; }
private:
    void setState(State newState){state_=newState;}
    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();
    void sendInLoop(const void* message, size_t len);//
    void shutdownInLoop();

    EventLoop *loop_;
    std::string name_;
    const InetAddress localAddr_;
    const InetAddress peerAddr_;//客户端的地址
    std::atomic_int state_;
    bool reading_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    ConnectionCallback connectionCallback_; // 有新连接时的回调
    MessageCallback messageCallback_; // 有读写消息时的回调
    WriteCompleteCallback writeCompleteCallback_; // 消息发送完成以后的回调
    HighWaterMarkCallback highWaterMarkCallback_;//高水位回调
    CloseCallback closeCallback_;

    size_t highWaterMark_;//数据水位线

    Buffer inputBuffer_;  // 接收数据的缓冲区
    Buffer outputBuffer_; // 发送数据的缓冲区
};
}


#endif