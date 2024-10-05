#include "EventLoop.h"
#include <sys/eventfd.h>
#include "channel.h"
#include "qlc_log.h"
#include <unistd.h>
#include <errno.h>
// #include "Poller.h"
namespace qlc{
static qlc::Logger::ptr g_logger =QLC_LOG_NAME("system");

__thread EventLoop* t_loopInThisThread=nullptr;//一个线程只有一个eventloop

const int KPollTimeMs=10000;
//创建wakeupfd，用来notify唤醒subReactor处理新来的channel
int createEventfd(){
    int efd=::eventfd(0,EFD_CLOEXEC|EFD_NONBLOCK);
    if(efd<0){
        QLC_LOG_ERROR(g_logger)<<"eventfd create failed errno="<<errno;
    }
    return efd;
}

EventLoop::EventLoop()
        :looping_(false)
        ,quit_(false)
        ,threadId_(CurrentThread::tid())
        ,poller_(Poller::newDefaultPlloer(this))
        ,wakeupFd_(createEventfd())
        ,wakeupChannel_(new Channel(this,wakeupFd_))
        ,callingPendingFunctors_(false)
{
    QLC_LOG_DEBUG(g_logger)<<"EventLoop created address="<<this<<"threadID="<<threadId_;
    if (t_loopInThisThread)
    {
        QLC_LOG_FATAL(g_logger)<<"Another EventLoop"<<t_loopInThisThread<<"exists in this threadID "<< threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
    // 设置wakeupfd的事件类型以及发生事件后的回调操作
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));//它调用 this 对象的 handleRead 方法
    // 每一个eventloop都将监听wakeupchannel的EPOLLIN读事件了
    wakeupChannel_->enableReading();
}
EventLoop::~EventLoop()
{
    wakeupChannel_->disableAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

// 开启事件循环  相当于是启动epoll
void EventLoop::loop()
{
    looping_ = true;
    quit_ = false;

    QLC_LOG_DEBUG(g_logger)<<"eventLoop"<<this<<"start looping";

    while(!quit_)
    {
        activeChannels_.clear();//每次执行完都清空
        // 监听两类fd   一种是client的fd，一种wakeupfd
        pollReturnTime_ = poller_->poll(KPollTimeMs, &activeChannels_);
        for (Channel *channel : activeChannels_)
        {
            // Poller监听哪些channel发生事件了，然后上报给EventLoop，通知channel处理相应的事件
            channel->handleEvent(pollReturnTime_);
        }
        // 执行当前EventLoop事件循环需要处理的回调操作
        /**
         * IO线程 mainLoop accept fd《=channel subloop
         * mainLoop 事先注册一个回调cb（需要subloop来执行） wakeup subloop后，执行下面的方法，执行之前mainloop注册的cb操作
         */ 
        doPendingFunctors();//相当于可能是要对新来的fd进行封装之类的回调需要sub做
    }

    QLC_LOG_DEBUG(g_logger)<<"eventLoop"<<this<<"stop looping";
    looping_ = false;
}
//分一个主loop和次loop 
void EventLoop::quit()
{
    //不是自己的线程调用的
    quit_=true;
    //如果是其他线程调用的这个loop的quit方法  相当于是在subloop的线程中 这个对象调用了mainloop的quit方法 那肯定要先唤醒
    //说明本来的线程可能正在阻塞
    if(!isInLoopThread()){
        wakeup();
    }
}
//在当先loop中执行cv
void EventLoop::runInLoop(Functor cb)
{
    if (isInLoopThread()) // 在当前的loop线程中，执行cb
    {
        cb();
    }
    else // 在非当前loop线程中执行cb , 就需要唤醒loop所在线程，执行cb
    {
        queueInLoop(cb);//可能是sub2调用sub3的cb
    }
}

void EventLoop::queueInLoop(Functor cb)
{
    {
        MutexType::Lock lock(mutex_);
        pendingFunctors_.emplace_back(cb);
    }

    // 唤醒相应的，需要执行上面回调操作的loop的线程了
    // || callingPendingFunctors_的意思是：当前loop正在执行回调，但是loop又有了新的回调
    if (!isInLoopThread() || callingPendingFunctors_) 
    {
        wakeup(); // 唤醒loop所在线程
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        QLC_LOG_FMT_ERROR(g_logger,"EventLoop::handle() writes %lu bytes instead of 8 \n", n);
    }
}

void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functions;
    callingPendingFunctors_=true;
    {
        MutexType::Lock lock(mutex_);
        functions.swap(pendingFunctors_);
    }
    for(auto function:functions){
        function();
    }
    callingPendingFunctors_=false;

}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        QLC_LOG_FMT_ERROR(g_logger,"EventLoop::wakeup() writes %lu bytes instead of 8 \n", n);
    }
}
// EventLoop的方法 =》 Poller的方法
void EventLoop::updateChannel(Channel *channel)
{
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel *channel)
{
    poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel *channel)
{
    return poller_->hasChannel(channel);
}

}