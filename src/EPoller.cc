//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EPoller.h>

#include <sys/epoll.h>

veri::EPoller::EPoller(veri::EventLoop &loop): Poller(loop), epoll_fd_(::epoll_create(1)), epoll_events_(SIZE) {

}


int veri::EPoller::poll(int timeout_ms, veri::Poller::ChannelList &active_channels) {
    int nfds = ::epoll_wait(epoll_fd_, epoll_events_.data(), static_cast<int>(epoll_events_.size()), timeout_ms);

    for (int i = 0; i < nfds; ++i) {
        int fd = epoll_events_[i].data.fd;
        auto iter = channels_.find(fd);
        if (iter != channels_.end()) {
            Channel *channel = iter->second;
            active_channels.push_back(channel);
        }
    }

    return nfds;
}
