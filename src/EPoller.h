//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_EPOLLER_H
#define VERINET_EPOLLER_H

#include <Poller.h>
#include <sys/epoll.h>

namespace veri {

class EPoller: public Poller {
  public:
    typedef std::vector<struct epoll_event> EPollEventsList;
    EPoller(EventLoop &loop);
    ~EPoller() {}

    virtual int poll(int timeout_ms, ChannelList &active_channels);

  private:

    int epoll_fd_;
    EPollEventsList epoll_events_;

};

}

#endif //VERINET_EPOLLER_H
