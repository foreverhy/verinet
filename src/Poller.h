//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_POLLER_H
#define VERINET_POLLER_H


namespace veri {


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

class Poller {

};

}


#endif //VERINET_POLLER_H
