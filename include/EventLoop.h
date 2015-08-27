//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_EVENTLOOP_H
#define VERINET_EVENTLOOP_H

#include <nocopyable.h>

#include <atomic>
#include <thread>

namespace veri {

class EventLoop: nocopyable {
  public:
    EventLoop();
    ~EventLoop();
    void loop();

  private:
    std::atomic_bool looping_;
    std::thread::id tid_;
};

}



#endif //VERINET_EVENTLOOP_H
