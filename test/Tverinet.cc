//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EventLoop.h>
#include <Channel.h>
#include <gtest/gtest.h>

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

void foo() {
    std::cout << "== FOO ==" << std::endl;
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
}

TEST(EPoll, basic) {
    veri::EventLoop loop;
    veri::Channel channel(loop, fileno(stdin));
    channel.set_reading(true);
    channel.set_readcb(foo);
    loop.update_channel(channel);
    loop.loop();
}

