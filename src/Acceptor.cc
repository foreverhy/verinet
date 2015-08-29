//
// Author: Yao Han <verihy@gmail.com>
// 

#include <Acceptor.h>
#include <EventLoop.h>


veri::Acceptor::Acceptor(veri::EventLoop &loop): loop_(loop), acc_channel_(loop, acc_socket_.fd()) {
    acc_socket_.set_reuseaddr();
}


void veri::Acceptor::bind(const veri::InetAddress &inetaddr) {
    acc_socket_.bind(inetaddr);
}


void veri::Acceptor::listen() {
    acc_socket_.listen();
    update_channel();
}


void veri::Acceptor::update_channel() {
    acc_channel_.set_reading(true);
    acc_channel_.set_readcb(std::bind(new_conn_cb_, acc_socket_.fd()));
    loop_.update_channel(acc_channel_);
}
