#include "Poller.h"
#include <sys/epoll.h>

namespace qlc{

class EpollPoller : public Poller{
public:
    EpollPoller(EventLoop *loop);
    ~EpollPoller() override;
    //重写方法
    Timestamp poll(int timeoutMS, ChannelList*activeChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;

private:
    static const int kInitEventListSize = 16;//代表一次可以返回的最大连接数
    // 填写活跃的连接
    enum{
        kNew=-1,//表示这个fd从来没添加到epoll  对应channel的成员index_ = -1
        kAdded=1,//表示已经添加到了
        kDeleted=2//表示一个channel已经从epoll删除了
    };
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    // 更新channel通道
    void update(int operation, Channel *channel);//相当于对chanel里面的fd更新events

    using EventList = std::vector<epoll_event>;
//struct epoll_event {
//     uint32_t events;  // epoll 事件类型，包括可读，可写等
//     epoll_data_t data; // 用户数据，可以是一个指针或文件描述符等  里面包含了发生事件的fd
// };
    int epollfd_;
    EventList events_;//epoll_wait
    //int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);  //返回需要处理事件的个数
//  struct epoll_event * events： 接口的返回参数，epoll把发生的事件的集合从内核复制到 events数组中。
//  events数组是一个用户分配好大小的数组，数组长度大于等于maxevents。
//  （events不可以是空指针，内核只负责把数据复制到这个 events数组中，不会去帮助我们在用户态中分配内存）
};

}