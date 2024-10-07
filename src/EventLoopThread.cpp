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
    std::cout<<"startLoop"<<std::endl;
    thread_.start(); // 启动底层的新线程  然后那个线程函数会运行
    EventLoop *loop = nullptr;
    {
        // std::cout<<"get lock"<<std::endl;
        
        // std::cout<<"cond_ wait begin"<<std::endl;
        while (loop_==nullptr)
        {
            //std::cout<<"cond_ wait"<<std::endl;
            cond_.wait();
        }
        // std::cout<<"cond_ wait end"<<std::endl;
        MutexType::Lock lock(mutex_);
        loop=loop_;
        
    }
    return loop;
}

void qlc::EventLoopThread::threadFunc()
{
    EventLoop loop; // 创建一个独立的eventloop，和上面的线程是一一对应的，one loop per thread
    std::cout<<"event loop create"<<std::endl;
    if (callback_)
    {
        callback_(&loop);
    }
    {
        // std::cout<<"function threadFunc0"<<std::endl;
        MutexType::Lock lock(mutex_);
        loop_ = &loop;
        // std::cout<<"function threadFunc1"<<std::endl;
        cond_.notify();
        // std::cout<<"function threadFunc2"<<std::endl;
    }
    loop.loop();//开始运行
    MutexType::Lock lock(mutex_);
    loop_=nullptr;
}
}