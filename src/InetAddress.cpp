#include "InetAddress.h"
#include <string.h>
namespace qlc{

InetAddress::InetAddress(uint16_t port,std::string ip){
    bzero(&addr_,sizeof(addr_));
    addr_.sin_family=AF_INET;
    addr_.sin_port=htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());//inet_addr函数转换网络主机地址（如192.168.1.10)为网络字节序二进制值
}

std::string InetAddress::toIP() const{


// int inet_pton(int family, const char *strptr, void *addrptr);     //将点分十进制的ip地址转化为用于网络传输的数值格式
//         返回值：若成功则为1，若输入不是有效的表达式则为0，若出错则为-1
 
// const char * inet_ntop(int family, const void *addrptr, char *strptr, size_t len);     //将数值格式转化为点分十进制的ip地址格式
//         返回值：若成功则为指向结构的指针，若出错则为NULL
    char buf[64]={0};
    ::inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof(buf));
    return buf;

}
std::string InetAddress::toIpPort() const{
    char buf[64]={0};
    ::inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof(buf));
    size_t end =strlen(buf);
    uint16_t port=ntohs(addr_.sin_port);
    sprintf(buf+end,":%u",port);
    //int sprintf(char* str, const char* format, ...);
    //str：指向要写入的字符串的指针
    //format：包含格式控制符的字符串，用于指定输出的格式。
    return buf;
}
uint16_t InetAddress::toPort() const{
    return ntohs(addr_.sin_port);
}


}