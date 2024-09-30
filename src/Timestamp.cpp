#include "Timestamp.h"
#include <time.h>
namespace qlc{

Timestamp::Timestamp():microSecondsSinceEpoch_(0) {}
Timestamp::Timestamp(int64_t microSecondsSinceEpoch)
    : microSecondsSinceEpoch_(microSecondsSinceEpoch)
    {}

Timestamp Timestamp::now()
{
    return Timestamp(time(NULL));
}
//Localtime是一个 C/C++ 标准库函数，用于将时间戳（time_t 类型）转换为本地时间的结构体。
// 它接受一个指向 time_t 类型的指针作为参数，并返回一个指向 tm 结构体的指针，该结构体包含了年、月、日、时、分、秒等时间信息。

//strftime(buf,sizeof(buf),m_format.c_str(),&tm);    
//用于日期和时间格式化的函数，它允许你将一个 tm 结构体表示的时间转换成一个基于指定格式的字符串。

std::string Timestamp::toString() const
{
    char buf[128] = {0};
    tm *tm_time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d", 
        tm_time->tm_year + 1900,
        tm_time->tm_mon + 1,
        tm_time->tm_mday,
        tm_time->tm_hour,
        tm_time->tm_min,
        tm_time->tm_sec);
    return buf;
}

}