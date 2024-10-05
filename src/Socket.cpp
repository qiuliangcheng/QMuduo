#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "InetAddress.h"
#include "qlc_log.h"
#include <netinet/tcp.h>

namespace qlc{
static qlc::Logger::ptr g_logger =QLC_LOG_NAME("system");
const int MAX_LEN_LISTEN=1024;
Socket::~Socket()
{
    ::close(sockfd_);
}

void Socket::bindAddress(const InetAddress &localaddr)
{
    if(0!=::bind(sockfd_,(sockaddr*)localaddr.getAddr(),(socklen_t)(sizeof(sockaddr_in))))
    {
        QLC_LOG_FMT_ERROR(g_logger,"bind sockfd:%d fail \n", sockfd_);
    }
}
void Socket::listen()
{
    if (0 != ::listen(sockfd_, MAX_LEN_LISTEN))
    {
        QLC_LOG_FMT_ERROR(g_logger,"listen sockfd:%d fail \n", sockfd_);
    }
}
int Socket::accept(InetAddress *peeraddr)
{
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    bzero(&addr, sizeof addr);
    //下面这个函数可以直接设置对返回的connfd设置非阻塞
    int connfd = ::accept4(sockfd_, (sockaddr*)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
    }
    return connfd;//新的sockfd  操作系统会设置一个端口给他用来通信
}
void Socket::shutdownWrite()
{
    if (::shutdown(sockfd_, SHUT_WR) < 0)
    {
        QLC_LOG_FMT_ERROR(g_logger,"shutdownWrite error");
    }
}
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval);
}
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}
void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}
}