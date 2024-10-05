#include "EpollPoller.h"
#include "qlc_log.h"
#include "channel.h"
#include <string.h>
namespace qlc{
static qlc::Logger::ptr g_logger=QLC_LOG_NAME("system");

EpollPoller::EpollPoller(EventLoop *loop)
            :Poller(loop)//调用父类的构造方法
            ,epollfd_(::epoll_create(EPOLL_CLOEXEC))
            ,events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        QLC_LOG_FATAL(g_logger)<<"epo;; create failed "<<"error num= "<<errno<<
            "error str:"<<strerror(errno);
    }
}

EpollPoller::~EpollPoller()
{
    ::close(epollfd_);
}

Timestamp EpollPoller::poll(int timeoutMS, ChannelList *activeChannels)
{
    //events_.begin() 返回的类型是 std::vector<epoll_event>::iterator  
    //std::vector<int>::iterator it = vec.begin();

    // 通过迭代器访问第一个元素
    // int firstElement = *it; // 解引用迭代器以获取元素值，这里 firstElement 将被赋值为 1

    int numEvents=::epoll_wait(epollfd_,&*events_.begin(),static_cast<int>(events_.size()),timeoutMS);
    int saveErrno = errno;
    Timestamp now(Timestamp::now());
    if(numEvents>0){
        QLC_LOG_DEBUG(g_logger)<<numEvents<<"has happened";
        //将所有事件返回放到activeChannels里面  然后返回给eventloop 让他去进行事件分发
        fillActiveChannels(numEvents,activeChannels);
        if (numEvents >= (int)events_.size())
        {
            events_.resize(events_.size() * 2);
        }
    }else if(numEvents==0){
        QLC_LOG_DEBUG(g_logger)<<"epoll_wati timeout!";
    }else{
        if (saveErrno != EINTR)
        {
            errno = saveErrno;
            QLC_LOG_DEBUG(g_logger)<<"epoll_wati error!"<<" error number= "<<errno<<"error str:"<<strerror(errno);
        } 
    }
    return now;//返回当前的时间错
}
void EpollPoller::updateChannel(Channel *channel)
{
    // kNew=-1,//表示这个fd从来没添加到epoll  对应channel的成员index_ = -1
    // kAdded=1,//表示已经添加到了
    // kDeleted=2//表示一个channel已经从epoll删除了
    const int index=channel->index();
    QLC_LOG_DEBUG(g_logger)<<"fd="<<channel->fd()<<"index="<<index<<"events="<<channel->getEvents();
    if (index == kNew || index == kDeleted)
    {
        if (index == kNew)
        {
            int fd = channel->fd();
            Channels_[fd] = channel;
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }else{
        // int fd = channel->fd();
        if (channel->isNoneEvent())//如果fd没有任何感兴趣的事件 就把他从epoll里面移除
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}
void EpollPoller::removeChannel(Channel *channel)
{
    int fd = channel->fd();
    Channels_.erase(fd);
    int index = channel->index();
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);//因为可能有事件 但是是自己手动删除的

}
// 填写活跃的连接
void EpollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const
{
    for (int i=0; i < numEvents; ++i)
    {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel); // EventLoop就拿到了它的poller给它返回的所有发生事件的channel列表了
    }
}
void EpollPoller::update(int operation, Channel *channel)
{
    epoll_event event;
    bzero(&event, sizeof(event));
    int fd=channel->fd();
    event.events = channel->getEvents();
    event.data.fd = fd; 
    event.data.ptr = channel;
    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
           QLC_LOG_ERROR(g_logger)<<"epoll_ctl del error!"<<" error number= "<<errno<<"error str:"<<strerror(errno);
        }
        else
        {
            QLC_LOG_ERROR(g_logger)<<"epoll_ctl add/mod error!"<<" error number= "<<errno<<"error str:"<<strerror(errno);
        }
    }

}
}
