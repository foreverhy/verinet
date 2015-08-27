//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_POLLER_H
#define VERINET_POLLER_H


#include <nocopyable.h>

#include <vector>
#include <map>

namespace veri {

class EventLoop;
class Channel;


enum POLL_EVENTS {
    POLLIN = 0x001,
    POLLPRI = 0x002,
    POLLOUT = 0x004,
    POLLRDNORM = 0x040,
    POLLRDBAND = 0x080,
    POLLWRNORM = 0x100,
    POLLWRBAND = 0x200,
    POLLMSG = 0x400,
    POLLERR = 0x008,
    POLLHUP = 0x010,
    POLLRDHUP = 0x2000,
    POLLWAKEUP = 1u << 29,
    POLLONESHOT = 1u << 30,
    POLLET = 1u << 31
};

class Poller: nocopyable {
  public:
    typedef std::vector<Channel*> ChannelList;
    typedef std::map<int, Channel*> ChannelMap;
    Poller(EventLoop *loop): loop_(loop) {}
    virtual ~Poller() = 0;

    virtual int poll(int timeout_ms, ChannelList *active_channels);

    virtual void update_channel(Channel *channel);

  protected:

    static const int SIZE = 1024;
    EventLoop *loop_;

    ChannelMap channels_;

};

}


#endif //VERINET_POLLER_H
