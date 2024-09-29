#ifndef __QLC_NONCOPYABLE_H
#define __QLC_NONCOPYABLE_H

namespace qlc{
class Noncopyable{
public:
    Noncopyable(const Noncopyable&)=delete;
    Noncopyable& operator=(const Noncopyable&)=delete;
    Noncopyable()=default;
    //加个注释
    ~Noncopyable()=default;
};

}
#endif