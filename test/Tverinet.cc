//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EventLoop.h>
#include <gtest/gtest.h>

#include <thread>

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
    loop.loop();
}

