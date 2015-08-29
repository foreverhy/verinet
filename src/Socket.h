//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_SOCKET_H
#define VERINET_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>

#include <InetAddress.h>
#include <nocopyable.h>
#include <unistd.h>

namespace veri {

class Socket: nocopyable {
  public:
    Socket(): socket_fd_(::socket(AF_INET, SOCK_STREAM, 0)) {}
    ~Socket() { ::close(socket_fd_); }

    void set_reuseaddr();
    void bind(const InetAddress &inet_addr);
    void listen();
    int accept();

    int fd() const { return socket_fd_; }


  private:
    const int socket_fd_;
};

}


#endif //VERINET_SOCKET_H
