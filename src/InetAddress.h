//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_INETADDRESS_H
#define VERINET_INETADDRESS_H

#include <arpa/inet.h>

#include <string>
#include <cstring>



namespace veri {

class InetAddress {
  public:
    InetAddress(const std::string &addr, const uint16_t port);
    explicit InetAddress(const uint16_t port);
    InetAddress(const struct sockaddr_in &inet_addr) { inet_addr_ = inet_addr; }
    ~InetAddress() {}

    uint16_t port() const { return ::ntohs(inet_addr_.sin_port); }
    std::string addr() const {
        char ret[32];
        ::inet_ntop(AF_INET, &inet_addr_.sin_addr, ret, sizeof ret);
        return std::string(ret);
    }

    const struct sockaddr_in& sockaddr_in() const { return inet_addr_; }

  private:
    struct sockaddr_in inet_addr_;

};

}


#endif //VERINET_INETADDRESS_H
