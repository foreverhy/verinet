//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EventLoop.h>
#include <Log.h>
#include <EPoller.h>
#include <Channel.h>

#include <poll.h>
#include <sys/eventfd.h>

#include <cassert>
#include <unistd.h>

namespace veri {

thread_local EventLoop* loop_in_this_thread = nullptr;

}


veri::EventLoop::EventLoop(): looping_(false), tid_(std::this_thread::get_id()), poller_(new EPoller(*this)),
                              wakeup_fd_(::eventfd(0, 0)), wakeup_channel_(new Channel(*this, wakeup_fd_)) {
    if (loop_in_this_thread) {
        LOG_FATAL("Already has a loop in this thread");
    } else {
        loop_in_this_thread = this;
    }
    wakeup_channel_->set_reading(true);
    wakeup_channel_->set_readcb(std::bind(&EventLoop::wakeup_handle, this));
    update_channel(*wakeup_channel_);
}


veri::EventLoop::~EventLoop() {
    assert(loop_in_this_thread == this);
    loop_in_this_thread = nullptr;
    delete wakeup_channel_;
    ::close(wakeup_fd_);
}

bool veri::EventLoop::in_loop_thread() {
    return this == loop_in_this_thread;
}

void veri::EventLoop::remove_channel(int fd) {
    poller_->remove_channel(fd);
}


void veri::EventLoop::remove_channel(Channel &channel) {
    poller_->remove_channel(channel);
}


void veri::EventLoop::update_channel(Channel &channel) {
    poller_->update_channel(channel);
}

void veri::EventLoop::wakeup_handle() {
    uint64_t u;
    ::read(wakeup_fd_, &u, sizeof u);
}

void veri::EventLoop::wakeup() {
    uint64_t u = 1;
    ::write(wakeup_fd_, &u, sizeof u);
}

void veri::EventLoop::loop() {
    assert(!looping_);
    assert(in_loop_thread());

    looping_ = true;

    while (looping_) {
        active_channels_.clear();
        poller_->poll(5000, active_channels_);
        for (size_t i = 0; i < active_channels_.size(); ++i) {
            active_channels_[i]->handle();
        }
    }

    looping_ = false;

}
