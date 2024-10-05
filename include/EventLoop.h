#ifndef __EVENTLOOP_H
#define __EVENTLOOP_H
//事件分发器 channel和epoll的联系都通过eventloop进行连接的
//eventloop通过调用poller 来增加fd 以及poller通过将事件告诉eventloop 让eventloop来调用驱动事件
#include <functional>
#include <vector>
#include <memory>
#include <atomic>
#include "mutex.h"
#include "Timestamp.h"
#include "noncopyable.h"
#include "Poller.h"
#include "util.h"
class Channel;
// class Poller;
namespace qlc{
class EventLoop:public Noncopyable{
public:
    using MutexType=Mutex;
    using Functor = std::function<void()>;//回调函数
    EventLoop();
    ~EventLoop();
    // 开启事件循环
    void loop();
    // 退出事件循环
    void quit();
    Timestamp pollReturnTime() const { return pollReturnTime_; }//肯定是调用poll得到的
    // 在当前loop中执行cb
    void runInLoop(Functor cb);
    // 把cb放入队列中，唤醒loop所在的线程，执行cb
    void queueInLoop(Functor cb);
    // 用来唤醒loop所在的线程的
    void wakeup();
    // EventLoop的方法 =》 Poller的方法
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);
    // 判断EventLoop对象是否在自己的线程里面
    bool isInLoopThread() const { return threadId_ ==  CurrentThread::tid(); }
private:
    void handleRead(); // wake up
    void doPendingFunctors(); //执行回调
    using ChannelList = std::vector<Channel*>;//一个eventloop里面有多少个事件  因为poller里面不一定有那么多事件 里面有的肯定都在eventloop里面
    std::atomic_bool looping_;//是否开启事件循环
    std::atomic_bool quit_;//退出
    const pid_t threadId_; // 记录当前loop所在线程的id
    Timestamp pollReturnTime_; // poller返回发生事件的channels的时间点 返回的时候发生的事件都在activatechannel里面了
    std::unique_ptr<Poller> poller_;
    //Poller* poller_;
    //他这边设置的是一个主要的eventloop用来除了accept得到的fd 然后唤醒其他的线程的eventloop 进行event_wait的操作啥的
    //这边用到的机制是唤醒 通知操作
    int wakeupFd_; // 主要作用，当mainLoop获取一个新用户的channel，通过轮询算法选择一个subloop，通过该成员唤醒subloop处理channel
    std::unique_ptr<Channel> wakeupChannel_;//用来accept的 channel 因为这边所有的fd都是用channel来代替
    //Channel *wakeupChannel_;
    ChannelList activeChannels_;
    std::atomic_bool callingPendingFunctors_; // 标识当前loop是否有需要执行的回调操作
    std::vector<Functor> pendingFunctors_; // 存储loop需要执行的所有的回调操作
    MutexType mutex_;
};

}
#endif