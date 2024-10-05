#include "channel.h"
#include <sstream>
#include <sys/epoll.h>
#include "EventLoop.h"

namespace qlc{
// epoll事件：
//    EPOLLIN ： 表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
//    EPOLLOUT： 表示对应的文件描述符可以写；
//    EPOLLPRI： 表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
//    EPOLLERR： 表示对应的文件描述符发生错误；
//    EPOLLHUP： 表示对应的文件描述符被挂断；

const int Channel::kNoneEvent=0;
const int Channel::kReadEvent=EPOLLIN|EPOLLPRI;
const int Channel::kWriteEvent=EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
                :loop_(loop)
                ,fd_(fd)
                ,events_(0)
                ,revents_(0)
                ,index_(-1)
                ,tied_(false)
{

}

Channel::~Channel()
{
 
}

void Channel::handleEvent(Timestamp receiveTime)
{ 
    std::shared_ptr<void> guard;
    if(tied_){
        guard=tie_.lock();
        if(guard){
            handleEventWriteGuard(receiveTime);
        }
    }
    else{
        handleEventWriteGuard(receiveTime);
    }

}
//什么时候调用这个方法？
void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_=obj;
    tied_=true;
}

// 改变事件后 要在epoll里面更改事件
// Eventloop 包含 channelList 和 epoll
void Channel::update()
{
    //通过eventpoll 调用epoll的方法 注册fd的event事件
    //TODO add code about channel in eventloop
    loop_->updateChannel(this);
}

void Channel::handleEventWriteGuard(Timestamp receiveTime)
{
    if((revents_&EPOLLHUP)&&!(revents_&EPOLLIN)){
        if(closeCallback_){
            closeCallback_();
        }
    }
    if((revents_&EPOLLERR)){
        if(errorCallback_){
            errorCallback_();
        }
    }
    if((revents_&(EPOLLIN|EPOLLPRI))){
        if(readCallback_){
            readCallback_(receiveTime);
        }
    }
    if(revents_&EPOLLOUT){
        if(writeCallback_){
            writeCallback_();
        }
    }
}
void Channel::remove() // 在channel所属的eventloop中 删除这个channel
{
    loop_->removeChannel(this);
}

}