#ifndef __THREADc11_H
#define __THREADc11_H
#include "noncopyable.h"
#include <functional>
#include <thread>//C++11自带的额thread库
#include <memory>
#include "mutex.h"
#include <string>
#include <unistd.h>
namespace qlc{

class ThreadC11:public Noncopyable{
public:
    using threadFunc=std::function<void()>;
    explicit ThreadC11(threadFunc cb, const std::string &name = std::string());
    ~ThreadC11()=default;
    void start();//这个得手动调用start函数开启线程
    void join();
    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    static int numCreated() { return numCreated_; }//创建了多少个线程 静态的有多少个类本质上都是同一个计数变量
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;//因为线程用的话会直接创建 我们希望能够手动控制线程的开启与关闭
    pid_t tid_;
    threadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
    Semaphore m_semaphore;



};

}




#endif