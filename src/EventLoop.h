//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_EVENTLOOP_H
#define VERINET_EVENTLOOP_H

#include <nocopyable.h>

#include <atomic>
#include <thread>
#include <memory>
#include "Channel.h"

namespace veri {
class Poller;
class Channel;

class EventLoop: nocopyable {
  public:
    typedef std::vector<Channel*> ChannelList;
    EventLoop();
    ~EventLoop();
    void loop();

    void update_channel(Channel &channel);
    void remove_channel(Channel &channel);
    void remove_channel(int fd);

    void wakeup();

  private:

    void wakeup_handle();
    bool in_loop_thread();

    std::atomic_bool looping_;
    std::thread::id tid_;

    std::unique_ptr<Poller> poller_;
    int wakeup_fd_;
    Channel *wakeup_channel_;

    ChannelList active_channels_;

};

}



#endif //VERINET_EVENTLOOP_H
