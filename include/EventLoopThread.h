#ifndef __ELTHREAD_H
#define __ELTHREAD_H
#include "ThreadC11.h"
#include "noncopyable.h"
#include <string>
#include <condition_variable>//条件变量

namespace qlc{
class EventLoop;
//一个线程上运行一个eventloop 
class EventLoopThread:public Noncopyable{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>; //线程初始化的回调函数
    using MutexType=Mutex;
    EventLoopThread(const ThreadInitCallback &cb,const std::string &name = std::string());
    ~EventLoopThread();
    EventLoop* startLoop();
private:
    void threadFunc();//线程运行的函数
    EventLoop *loop_;//线程里所拥有的eventloop
    bool exiting_;
    ThreadC11 thread_;
    MutexType mutex_;
    Semaphore cond_;//void wait(unique_lock<mutex>& lock);
    ThreadInitCallback callback_;
};



}

#endif