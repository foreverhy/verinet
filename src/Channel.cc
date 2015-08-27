//
// Author: Yao Han <verihy@gmail.com>
// 

#include "Channel.h"


veri::Channel::Channel(veri::EventLoop *loop, int fd):loop_(loop), fd_(fd) {

}


void veri::Channel::set_reading(bool on) {
    if (on) {
        events_ |= (POLL_EVENTS::POLLIN | POLL_EVENTS::POLLPRI);
    } else {
        events_ &= ~POLL_EVENTS::POLLIN;
    }
}


void veri::Channel::set_writeing(bool on) {
    if (on) {
        events_ |= POLL_EVENTS::POLLOUT;
    } else {
        events_ &= ~POLL_EVENTS::POLLOUT;
    }
}


void veri::Channel::handle() {

    if (revents_ & POLL_EVENTS:: POLLERR) {
        if (close_cb_) {
            close_cb_();
        }
    }

    if (revents_ & (POLL_EVENTS::POLLIN | POLL_EVENTS::POLLPRI)) {
        if (read_cb_) {
            read_cb_();
        }
    }

    if (revents_ & POLL_EVENTS::POLLOUT) {
        if (write_cb_) {
            write_cb_();
        }
    }

}
