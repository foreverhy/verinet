//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_CHANNEL_H
#define VERINET_CHANNEL_H

#include <nocopyable.h>
#include <Poller.h>

#include <functional>
#include <utility>

namespace veri {

class EventLoop;

class Channel: nocopyable {
  public:
    typedef std::function<void()> CallbackFn;

    Channel(EventLoop &loop, int fd);
    ~Channel() {}

    int fd() const { return fd_; }
    int events() const { return events_; }
    int revents() const { return revents_; }
    EventLoop& loop() const { return loop_; }

    void set_revents(uint32_t revents) { revents_ = revents; }

    void set_readcb(const CallbackFn &cb) { read_cb_ = cb; }
    void set_writecb(const CallbackFn &cb) { write_cb_ = cb; }
    void set_closecb(const CallbackFn &cb) { close_cb_ = cb; }

    void set_readcb(CallbackFn &&cb) { read_cb_ = std::move(cb); }
    void set_writecb(CallbackFn &&cb) { write_cb_ = std::move(cb); }
    void set_closecb(CallbackFn &&cb) { close_cb_ = std::move(cb); }

    void set_reading(bool on);
    void set_writeing(bool on);
    void clear_events() { events_ = 0; }

    void handle();


  private:

    EventLoop &loop_;
    const int fd_;

    uint32_t events_;
    uint32_t revents_;

    CallbackFn read_cb_;
    CallbackFn write_cb_;
    CallbackFn close_cb_;

};

}

#endif //VERINET_CHANNEL_H
