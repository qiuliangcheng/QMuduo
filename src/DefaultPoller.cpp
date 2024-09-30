#include <stdlib.h>
#include "EpollPoller.h"
#include "Poller.h"
namespace qlc{

Poller* Poller::newDefaultPlloer(EventLoop *loop){
    if(::getenv("MUDUO_USE_POLL")){
        return nullptr;
    }
    else{
        return nullptr;
    }

}
}