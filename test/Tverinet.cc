//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EventLoop.h>
#include <Channel.h>
#include <InetAddress.h>
#include <Acceptor.h>
#include <gtest/gtest.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <thread>
#include <string>

#include <iostream>

void loop_func() {
    veri::EventLoop loop;
}

TEST(EventLoop, cons) {
    veri::EventLoop loop;
    std::thread t(loop_func);
    t.join();
}

TEST(EventLoop, loop) {
    veri::EventLoop loop;
//    loop.loop();
}

void foo(veri::EventLoop &loop, int fd) {
    std::cout << "== FOO ==" << std::endl;
    std::string s;
    if (std::cin >> s) {
        std::cout << s << std::endl;
    } else {
        loop.remove_channel(fd);
        ::close(fd);
    }
}

TEST(EPoll, basic) {
    veri::EventLoop loop;
    veri::Channel channel(loop, fileno(stdin));
    channel.set_reading(true);
    channel.set_readcb(std::bind(foo,std::ref(loop), fileno(stdin)));
    loop.update_channel(channel);
//    loop.loop();
}

#include <cstdio>

void bar(int listenfd) {
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    ::printf("=== BAR ===\n");
    int fd = ::accept(listenfd, (struct sockaddr*)&addr, &addr_len);
//    ::getpeername(fd, (struct sockaddr*)&addr, &addr_len);
    ::printf("New Conn from %s:%u\n", ::inet_ntoa(addr.sin_addr), ::ntohs(addr.sin_port));
    ::close(fd);
}

TEST(Acceptor, basic) {
    veri::EventLoop loop;
    veri::Acceptor acc(loop);
    veri::InetAddress addr("127.0.0.1", 8888);
    acc.bind(addr);
    acc.set_new_conn_cb(bar);
    acc.listen();
//    loop.loop();
}

#include <Buffer.h>

TEST(Buffer, basic) {
    veri::Buffer buffer;
    buffer.append("abcdefg");
    ASSERT_EQ(std::string("abcdefg"), buffer.retrive_all());
    ASSERT_EQ(std::string(), buffer.retrive_all());
    std::string tmp;
    buffer.append("abcdefg");
    for (int i = 0; i < 2048; ++i) {
        tmp += "1";
    }
    buffer.append(tmp);
    ASSERT_EQ(std::string("abcdefg") + tmp, buffer.retrive_all());
    ASSERT_EQ(std::string(), buffer.retrive_all());
}
