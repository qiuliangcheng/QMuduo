#ifndef __CHANNEL_H
#define __CHANNEL_H
#include <functional>
#include "Timestamp.h"
#include <memory>
namespace qlc{
//可以理解成一个fd的event 包含了返回的具体事件、包含的事件
class EventLoop;
class Channel{
public:
    using EventCallback=std::function<void()>;
    using ReadEventCallback=std::function<void(Timestamp)>;
    Channel(EventLoop *loop,int fd);
    ~Channel();
    //fd得到epoll的事件通知后  处理对应事件的函数
    void handleEvent(Timestamp receiveTime);
    //设置回调函数
    void setReadCallback(ReadEventCallback cb){readCallback_=std::move(cb);}//用move的原因是因为cb是一个对象 直接将资源转移 可以节省内存空间
    void setWriteCallback(EventCallback cb){writeCallback_=std::move(cb);}
    void setCloseCallback(EventCallback cb){closeCallback_=std::move(cb);}
    void setErrorCallback(EventCallback cb){errorCallback_=std::move(cb);}
    

    //防止当前的channel被手动remove掉 channel还在执行回调操作
    void tie(const std::shared_ptr<void>&obj);
    int fd() const {return fd_;}
    void set_revents(int revt) {revents_=revt;}
    
    void enableReading() {events_ |= kReadEvent;update();}//update是调用epoll来增加事件
    void disableReading() {events_ &= ~kReadEvent;update();}
    void enableWriting() {events_ |= kWriteEvent;update();}//update是调用epoll来增加事件
    void disableWriting() {events_ &= ~kWriteEvent;update();}
    void disableAll() {events_ =kNoneEvent;update();}

    //返回 fd当前状态
    bool isNoneEvent() const {return events_==kNoneEvent;}
    bool isWriteEvent() const {return events_==kWriteEvent;}
    bool isReadEvent() const {return events_==kReadEvent;}

    int index() const {return index_;}
    void set_index(int index){index_=index;}
    int getEvents()const {return events_;}
    EventLoop* ownerLoop() const {return loop_;}//返回当前的channel属于哪个eventloop
    void remove();
private:
    void update();
    void handleEventWriteGuard(Timestamp receiveTime);

    static const int kNoneEvent;//当前的状态 表示对什么事件感兴趣
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;//感兴趣的事件
    int revents_;//实际发生的事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;
    ReadEventCallback readCallback_;//事件的回调函数
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};


}
#endif