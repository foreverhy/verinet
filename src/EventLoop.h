//
// Author: Yao Han <verihy@gmail.com>
// 

#ifndef VERINET_EVENTLOOP_H
#define VERINET_EVENTLOOP_H

#include <nocopyable.h>

#include <atomic>
#include <thread>
#include <memory>

namespace veri {
class Poller;

class EventLoop: nocopyable {
  public:
    EventLoop();
    ~EventLoop();
    void loop();

  private:
    std::atomic_bool looping_;
    std::thread::id tid_;

    std::unique_ptr<Poller> poller_;


    bool in_loop_thread();
};

}



#endif //VERINET_EVENTLOOP_H
