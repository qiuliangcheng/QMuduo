#include "ThreadC11.h"
#include "util.h"

namespace qlc{

std::atomic_int ThreadC11::numCreated_(0);

ThreadC11::ThreadC11(threadFunc cb, const std::string &name)
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(cb))
    , name_(name)
{
    setDefaultName();//给这个线程设置一个名字
}

void ThreadC11::start()
{
    started_=true;

    thread_=std::shared_ptr<std::thread>(new std::thread([&](){
        tid_=CurrentThread::tid();
        m_semaphore.notify();//说明已经创建成功了额
        func_();
    }));
    m_semaphore.wait();//需要新线程真正开始跑起来了才能说线程创建完成
}
void ThreadC11::join()
{
}
void ThreadC11::setDefaultName()
{
    int num = ++numCreated_;
    if (name_.empty())
    {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}
}