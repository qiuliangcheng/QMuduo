#ifndef __QLC_SINGLETON_H__
#define __QLC_SINGLETON_H__
#include <memory>
namespace qlc{

template<class T, class X= void , int N = 0 >
class Singleton{
public:
//静态局部变量已经是现在安全的了
    static T* GetInstanceX() {
        static T v;
        return &v;
    }
};

template<class T, class X= void , int N = 0 >
class SingletonPtr{
    static std::shared_ptr<T> GetInstancePtr() {
        static std::shared_ptr<T> v(new T);
        return v;
    }


};

}

#endif