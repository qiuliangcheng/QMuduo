#ifndef __EVENTLOOPTHREADPOOL_H
#define __EVENTLOOPTHREADPOOL_H
#include "noncopyable.h"
#include <functional>
#include <vector>
#include <memory>
#include <string>
namespace qlc{
class EventLoop;
class EventLoopThread;

class EventLoopThreadPool :Noncopyable{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>; //线程池启动的回调函数 每个线程都会执行这个回调函数
    EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);//baseloop就是用来accept的那个loop 收到了就分给子Loop
    ~EventLoopThreadPool();
    void setThreadNum(int numThreads) { numThreads_ = numThreads; }
    void start(const ThreadInitCallback &cb);
    // 如果工作在多线程中，baseLoop_默认以轮询的方式分配channel给subloop
    EventLoop* getNextLoop();
    std::vector<EventLoop*> getAllLoops();//每个线程start都会返回运行在那个线程上的loop
    bool started() const { return started_; }
    const std::string getPollName() const { return name_; }
private:

    EventLoop *baseLoop_; // EventLoop loop;  
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

}

#endif