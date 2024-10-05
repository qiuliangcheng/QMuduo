#include "EventLoopThread.h"
#include "EventLoop.h"

namespace qlc{

EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
        : loop_(nullptr)
        , exiting_(false)
        , thread_(std::bind(&EventLoopThread::threadFunc, this), name)
        , cond_()
        , callback_(cb)
{

}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if (loop_ != nullptr)
    {
        loop_->quit();
        thread_.join();
    }
}
EventLoop *EventLoopThread::startLoop()//启动线程运行loop并且返回该线程运行的那个Loop
{
    thread_.start(); // 启动底层的新线程  然后那个线程函数会运行
    EventLoop *loop = nullptr;
    {
        MutexType::Lock lock(mutex_);
        while (loop==nullptr)
        {
            cond_.wait();
        }
        loop=loop_;
        
    }
    return loop;
}

void qlc::EventLoopThread::threadFunc()
{
    EventLoop loop; // 创建一个独立的eventloop，和上面的线程是一一对应的，one loop per thread
    if (callback_)
    {
        callback_(&loop);
    }
    {
        MutexType::Lock lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }
    loop.loop();//开始运行
    MutexType::Lock lock(mutex_);
    loop_=nullptr;
}
}