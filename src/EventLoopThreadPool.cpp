#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"


namespace qlc{

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg)
    : baseLoop_(baseLoop)
    , name_(nameArg)
    , started_(false)
    , numThreads_(0)
    , next_(0)
{
}
EventLoopThreadPool::~EventLoopThreadPool(){

}
void EventLoopThreadPool::start(const ThreadInitCallback &cb)
{
    started_ = true;
    std::cout<<"EventLoopThreadPool start"<<std::endl;
    for (int i = 0; i < numThreads_; ++i)
    {
        std::cout<<"numThreads_"<<i<<std::endl;
        char buf[name_.size() + 32];
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        EventLoopThread *t = new EventLoopThread(cb, buf);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));//线程池里面的线程
        loops_.push_back(t->startLoop()); // 底层创建线程，绑定一个新的EventLoop，并返回该loop的地址
    }
    // 整个服务端只有一个线程，运行着baseloop
    if (numThreads_ == 0 && cb)
    {
        cb(baseLoop_);
    }
}
EventLoop *EventLoopThreadPool::getNextLoop()
{
    EventLoop *loop = baseLoop_;
    if (!loops_.empty()) // 通过轮询获取下一个处理事件的loop
    {
        loop = loops_[next_];
        ++next_;
        if (next_ >= (int)loops_.size())
        {
            next_ = 0;
        }
    }

    return loop;
}
std::vector<EventLoop *> EventLoopThreadPool::getAllLoops()
{
    if (loops_.empty())
    {
        return std::vector<EventLoop*>(1, baseLoop_);
    }
    else
    {
        return loops_;
    }
}
}