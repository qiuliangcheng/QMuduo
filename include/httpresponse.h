#include "copyable.h"
#include <map>
#include <string>
// HTTP/1.1 200 OK
// Content-Type: text/html; charset=UTF-8
// Content-Length: 125
// <html>
// <head>
//     <title>Example Page</title>
// </head>
// <body>
//     <p>Hello, World!</p>
// </body>
// </html>


namespace qlc{
class Buffer;

class HttpResponse:public copyable{

public:
    enum HttpStatusCode  //回复的状态
    {
        kUnknown,
        k200Ok = 200,
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404,
    };
    explicit HttpResponse(bool close)
        : statusCode_(kUnknown),
        closeConnection_(close)
    {

    }
    void setStatusCode(HttpStatusCode code)
    { statusCode_ = code; }

    void setStatusMessage(const std::string& message)
    { statusMessage_ = message; }

    void setCloseConnection(bool on)
    { closeConnection_ = on; }

    bool closeConnection() const
    { return closeConnection_; }

    void setContentType(const std::string& contentType)
    { addHeader("Content-Type", contentType); }

    // FIXME: replace string with StringPiece
    void addHeader(const std::string& key, const std::string& value)
    { headers_[key] = value; }

    void setBody(const std::string& body)
    { body_ = body; }

    void appendToBuffer(Buffer* output) const;
private:
    std::map<std::string, std::string> headers_;
    HttpStatusCode statusCode_;
    // FIXME: add http version  默认http 1.1
    std::string statusMessage_;
    bool closeConnection_;
    std::string body_;
}; 



}