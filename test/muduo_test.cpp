#include <iostream>
#include "TcpServer.h"
#include "qlc_log.h"
#include <functional>
#include <string>
static qlc::Logger::ptr g_logger=QLC_LOG_NAME("system");
class EchoServer
{
public:
    EchoServer(qlc::EventLoop *loop,
            const qlc::InetAddress &addr, 
            const std::string &name)
        : loop_(loop)
        , server_(loop, addr, name)

    {
        // 注册回调函数
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1)
        );

        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this,
                std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );

        // 设置合适的loop线程数量 loopthread
        server_.setThreadNum(3);
    }
    void start()
    {
        server_.start();
    }
private:
    // 连接建立或者断开的回调
    void onConnection(const qlc::TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            QLC_LOG_FMT_INFO(g_logger,"Connection UP : %s", conn->peerAddress().toIpPort().c_str());
        }
        else
        {
             QLC_LOG_FMT_INFO(g_logger,"Connection DOWN : %s", conn->peerAddress().toIpPort().c_str());
        }
    }

    // 可读写事件回调
    void onMessage(const qlc::TcpConnectionPtr &conn,
                qlc::Buffer *buf,
                qlc::Timestamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
        conn->shutdown(); // 写端   EPOLLHUP =》 closeCallback_
    }

    qlc::EventLoop *loop_;
    qlc::TcpServer server_;
};

int main(int argc,char** argv){
    qlc::EventLoop loop;
    qlc::InetAddress addr(8000);
    EchoServer server(&loop, addr, "EchoServer-01"); // Acceptor non-blocking listenfd  create bind 
    server.start(); // listen  loopthread  listenfd => acceptChannel => mainLoop =>
    loop.loop(); // 启动mainLoop的底层Poller
    return 0;
}