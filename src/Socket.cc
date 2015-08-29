//
// Author: Yao Han <verihy@gmail.com>
// 

#include <Socket.h>
#include <Log.h>


void veri::Socket::bind(const veri::InetAddress &inet_addr) {
    if ((::bind(socket_fd_, (struct sockaddr*)&inet_addr.sockaddr_in(), sizeof(inet_addr.sockaddr_in()))) < 0) {
        LOG_FATAL("Bind %s:%d error\n", inet_addr.addr().data(), inet_addr.port());
        std::abort();
    }
}


void veri::Socket::set_reuseaddr() {
    int yes = 1;
    ::setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
}


void veri::Socket::listen() {
    if ((::listen(socket_fd_, 1024)) < 0) {
        LOG_FATAL("Listen error\n");
        std::abort();
    }
}


int veri::Socket::accept() {
    int ret = ::accept(socket_fd_, NULL, NULL);
    return ret;
}
