#include <iostream>
#include "InetAddress.h"
#include "qlc_log.h"
static qlc::Logger::ptr g_logger=QLC_LOG_NAME("system");
int main(){
    qlc::InetAddress addr(9090);
    QLC_LOG_INFO(g_logger)<<addr.toIpPort();
}