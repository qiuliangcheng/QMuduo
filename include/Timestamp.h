#ifndef __TIMESTAMP_H
#define __TIMESTAMP_H
#include <iostream>
#include <string>
namespace qlc{

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    static Timestamp now();
    std::string toString() const;
    std::string toFormattedString(bool showMicroseconds = true) const;
    void swap(Timestamp& that)
    {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }
private:
    int64_t microSecondsSinceEpoch_;//毫秒时间点
    static const int kMicroSecondsPerSecond = 1000 * 1000;
};


}


#endif