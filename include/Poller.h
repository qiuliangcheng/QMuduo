#ifndef __QLC_POLL_H
#define __QLC_POLL_H
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <unordered_map>
#include "Timestamp.h"
#include "noncopyable.h"
namespace qlc{
class Channel;
class EventLoop;
class Poller:Noncopyable{
public:
    using ChannelList=std::vector<Channel*>;
    Poller(EventLoop* loop);
    virtual ~Poller()=default;
    //给所有IO复用保留统一的接口  因为子类可以是epoll poll select
    virtual Timestamp poll(int timeoutMS, ChannelList*activeChannels)=0;
    virtual void updateChannel(Channel* channel)=0;
    virtual void removeChannel(Channel* channel)=0;
    virtual bool hasChannel(Channel* channel) const;//判断这个channel 是不是在poller中
    static Poller* newDefaultPlloer(EventLoop* loop);
protected:
    using ChannelMap=std::unordered_map<int,Channel*>; //int：sockfd   对应的就是所属于的channel
    ChannelMap Channels_;
private:
    EventLoop* ownerLoop_;//定义所属的eventloop
};

}

#endif