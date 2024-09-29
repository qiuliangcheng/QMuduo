#ifndef __INET_ADDRESS_H
#define __INET_ADDRESS_H
#include <arpa/inet.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <stdint.h>
#include <string>
namespace qlc{

class InetAddress{

public:
    explicit InetAddress(uint16_t port,std::string ip="127.0.0.1");
    explicit InetAddress(sockaddr_in &addr):addr_(addr){};
    std::string toIP() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getAddr() const {return &addr_;}
private:
    sockaddr_in addr_;
};






}

#endif