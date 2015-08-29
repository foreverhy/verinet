//
// Author: Yao Han <verihy@gmail.com>
// 

#include "InetAddress.h"

veri::InetAddress::InetAddress(const std::string &addr, const uint16_t port) {
    std::memset(&inet_addr_, 0, sizeof inet_addr_);
    inet_addr_.sin_family = AF_INET;
    if (addr.data()) {
        ::inet_pton(AF_INET, addr.data(), &inet_addr_.sin_addr);
    } else {
        inet_addr_.sin_addr.s_addr = ::htonl(INADDR_ANY);
    }
    inet_addr_.sin_port = ::htons(port);
}


veri::InetAddress::InetAddress(const uint16_t port): InetAddress("", port) {

}
