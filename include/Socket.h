#ifndef __QLC_SOCKET_H
#define __QLC_SOCKET_H

#include "noncopyable.h"
namespace qlc{
class InetAddress;
//封装socket
class Socket:public Noncopyable{
public:
    explicit Socket(int sockfd)
        : sockfd_(sockfd)
    {}
    ~Socket();
    int getFd() const { return sockfd_; }
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);//将accept得到的ip地址 记录在peeraddr 里面
    void shutdownWrite();
    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);
private:
    const int sockfd_;
};

}
#endif