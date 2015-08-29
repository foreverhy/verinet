//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_ACCEPTOR_H
#define VERINET_ACCEPTOR_H

#include <Socket.h>
#include <Channel.h>
#include <InetAddress.h>

#include <functional>

namespace veri {

class EventLoop;

class Acceptor {
  public:
    typedef std::function<void(int)> NewConnCb;

    explicit Acceptor(EventLoop &loop);
    ~Acceptor() {}

    void bind(const InetAddress &inetaddr);

    void listen();

    void set_new_conn_cb(const NewConnCb &cb) { new_conn_cb_ = cb; }
    void set_new_conn_cb(NewConnCb &&cb) { new_conn_cb_ = std::move(cb); }

  private:

    void update_channel();

    EventLoop &loop_;
    Socket acc_socket_;
    Channel acc_channel_;

    NewConnCb new_conn_cb_;

};

}

#endif //VERINET_ACCEPTOR_H
