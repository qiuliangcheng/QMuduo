#include "httpserver.h"
#include "httpcontext.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "qlc_log.h"
#include "TcpConnection.h"
namespace qlc{
    static qlc::Logger::ptr g_logger =QLC_LOG_NAME("system");
    void defaultHttpCallback(const HttpRequest&, HttpResponse* resp)
    {
        resp->setStatusCode(HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
    }
    HttpServer::HttpServer(EventLoop* loop,
                        const InetAddress& listenAddr,
                        const string& name,
                        TcpServer::Option option)
    : server_(loop, listenAddr, name, option),
        httpCallback_(defaultHttpCallback)
    {
        server_.setConnectionCallback(
            std::bind(&HttpServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(
            std::bind(&HttpServer::onMessage, this, std::placeholders::_1,std::placeholders::_2, std::placeholders::_3));
    }
    void HttpServer::start()
    {
        QLC_LOG_DEBUG(g_logger) << "HttpServer[" << server_.getName()
            << "] starts listening on " << server_.getIpPort();
        server_.start();
    }

    void HttpServer::onConnection(const TcpConnectionPtr& conn)
    {
        if (conn->connected())
        {
            conn->setContext(HttpContext());
        }
    }
    void HttpServer::onMessage(const TcpConnectionPtr& conn,
                            Buffer* buf,
                            Timestamp receiveTime)
    {
        HttpContext* context =conn->getContextPtr();

        if (!context->parseRequest(buf, receiveTime))
        {
            conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
            conn->shutdown();
        }
        if (context->gotAll())
        {
            onRequest(conn, context->request());
            context->reset();
        }
    }
    void HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& req)
    {
        const string& connection = req.getHeader("Connection");
        bool close = connection == "close" ||
            (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");
        HttpResponse response(close);
        httpCallback_(req, &response);
        Buffer buf;
        response.appendToBuffer(&buf);
        conn->send(&buf);
        if (response.closeConnection())
        {
            conn->shutdown();
        }
    }
}
