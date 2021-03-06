//
// Author: Yao Han <verihy@gmail.com>
// 

#include <Channel.h>
#include <Log.h>


veri::Channel::Channel(veri::EventLoop &loop, int fd):loop_(loop), fd_(fd), events_(0), revents_(0) {

}


void veri::Channel::set_reading(bool on) {
    if (on) {
        events_ |= (POLL_EVENTS::IN | POLL_EVENTS::PRI);
    } else {
        events_ &= ~POLL_EVENTS::IN;
    }
}


void veri::Channel::set_writeing(bool on) {
    if (on) {
        events_ |= POLL_EVENTS::OUT;
    } else {
        events_ &= ~POLL_EVENTS::OUT;
    }
}


void veri::Channel::handle() {
    LOG_INFO("HANDLE for %d, revents is %u\n", fd_, revents_);

    if (revents_ & POLL_EVENTS:: ERR) {
        if (close_cb_) {
            close_cb_();
        }
    }

    if (revents_ & (POLL_EVENTS::IN | POLL_EVENTS::PRI)) {
        if (read_cb_) {
            read_cb_();
        }
    }

    if (revents_ & POLL_EVENTS::OUT) {
        if (write_cb_) {
            write_cb_();
        }
    }

    revents_ = 0;

}
