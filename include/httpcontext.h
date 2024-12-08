#ifndef _QLC_HTTPCONTEXT_H
#define _QLC_HTTPCONTEXT_H
#include <string>
#include "httprequest.h"
#include "copyable.h"
namespace qlc{

class Buffer;

class HttpContext :public copyable{

public:
    enum HttpRequestParseState
    {
        kExpectRequestLine,
        kExpectHeaders,//剩余头部
        kExpectBody,//剩余body
        kGotAll,//获得了所有状态
    };
    bool parseRequest(Buffer* buf, Timestamp receiveTime);

    bool gotAll() const
    { 
        return state_ == kGotAll; 
    }
    void reset()
    {
        state_ = kExpectRequestLine;
        HttpRequest dummy;
        request_.swap(dummy);
    }
    const HttpRequest& request() const{
        return request_;
    }
    HttpRequest& request(){
        return request_;
    }

private:
    bool processRequestLine(const char* begin, const char* end);//对http请求的每一行进行处理

    HttpRequestParseState state_;
    HttpRequest request_;

};




}


#endif