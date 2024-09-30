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
private:
    int64_t microSecondsSinceEpoch_;//毫秒时间点
};


}


#endif