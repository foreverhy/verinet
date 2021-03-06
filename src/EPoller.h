//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_EPOLLER_H
#define VERINET_EPOLLER_H

#include <Poller.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace veri {

class EPoller: public Poller {
  public:
    typedef std::vector<struct epoll_event> EPollEventsList;
    EPoller(EventLoop &loop);
    ~EPoller() { ::close(epoll_fd_); }

    virtual int poll(int timeout_ms, ChannelList &active_channels) override;

    virtual void update_channel(Channel &channel) override;

    virtual void remove_channel(int fd) override;

    virtual void remove_channel(Channel &channel) override;

  private:

    int epoll_fd_;
    EPollEventsList epoll_events_;

};

}

#endif //VERINET_EPOLLER_H
