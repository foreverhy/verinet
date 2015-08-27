//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EventLoop.h>
#include <Log.h>

#include <cassert>

#include <poll.h>
#include <EPoller.h>

namespace veri {

thread_local EventLoop* loop_in_this_thread = nullptr;

}


veri::EventLoop::EventLoop(): looping_(false), tid_(std::this_thread::get_id()), poller_(new EPoller(*this)) {
    if (loop_in_this_thread) {
        LOG_FATAL("Already has a loop in this thread");
    } else {
        loop_in_this_thread = this;
    }
}


veri::EventLoop::~EventLoop() {
    assert(loop_in_this_thread == this);
    loop_in_this_thread = nullptr;
}

bool veri::EventLoop::in_loop_thread() {
    return this == loop_in_this_thread;
}

void veri::EventLoop::loop() {
    assert(!looping_);
    assert(in_loop_thread());

    looping_ = true;

    ::poll(NULL, 0, 1000);

    looping_ = false;

}
