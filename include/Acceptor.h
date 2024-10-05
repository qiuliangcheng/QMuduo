#ifndef __QLC_ACCEPTOR_H
#define __QLC_ACCEPTOR_H
#include "noncopyable.h"
#include "Socket.h"
#include "channel.h"
#include <functional>
namespace qlc{
class InetAddress;
class EventLoop;
class Acceptor :Noncopyable{
public:
    using NewConnectionCallback=std::function<void(int sockfd, const InetAddress&)>;//新连接所需要调用的函数 那肯定需要把fd转成channel
    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();
    void setNewConnectionCallback(const NewConnectionCallback &cb) 
    {
        newConnectionCallback_ = cb;
    }
    bool listenning() const { return listenning_; }
    void listen();
private:
    void handleRead();//这个channel所得到的通知 然后调用的 做法肯定是要把新的channel通过轮询放到下一个loop里面的
    EventLoop *loop_; // Acceptor用的就是用户定义的那个baseLoop，也称作mainLoop
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;


};


}

#endif