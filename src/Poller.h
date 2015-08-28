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
    IN = 0x001,
    PRI = 0x002,
    OUT = 0x004,
    RDNORM = 0x040,
    RDBAND = 0x080,
    WRNORM = 0x100,
    WRBAND = 0x200,
    MSG = 0x400,
    ERR = 0x008,
    HUP = 0x010,
    RDHUP = 0x2000,
    WAKEUP = 1u << 29,
    ONESHOT = 1u << 30,
    ET = 1u << 31
};

class Poller: nocopyable {
  public:
    typedef std::vector<Channel*> ChannelList;
    typedef std::map<int, Channel*> ChannelMap;
    Poller(EventLoop &loop): loop_(loop) {}
    virtual ~Poller() {};

    virtual int poll(int timeout_ms, ChannelList &active_channels) = 0;

    virtual void update_channel(Channel &channel) = 0;

    virtual void remove_channel(Channel &channel) = 0;

    virtual void remove_channel(int fd) = 0;

  protected:

    static const int SIZE = 1024;
    EventLoop &loop_;

    ChannelMap channels_;

};

}


#endif //VERINET_POLLER_H
