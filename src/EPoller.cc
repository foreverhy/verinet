//
// Author: Yao Han <verihy@gmail.com>
// 

#include <EPoller.h>
#include <Channel.h>

#include <sys/epoll.h>

#include <cassert>


veri::EPoller::EPoller(veri::EventLoop &loop): Poller(loop), epoll_fd_(::epoll_create(1)), epoll_events_(SIZE) {

}


// FIXME: resize epoll_events_
int veri::EPoller::poll(int timeout_ms, veri::Poller::ChannelList &active_channels) {
    int nfds = ::epoll_wait(epoll_fd_, epoll_events_.data(), static_cast<int>(epoll_events_.size()), timeout_ms);

    for (int i = 0; i < nfds; ++i) {
        int fd = epoll_events_[i].data.fd;
        auto iter = channels_.find(fd);
        assert(iter != channels_.end());
        Channel *channel = iter->second;
        active_channels.push_back(channel);
    }

    return nfds;
}

void veri::EPoller::update_channel(veri::Channel &channel) {
    auto iter = channels_.find(channel.fd());
    int op = 0;
    if (iter == channels_.end()) {
        iter = channels_.insert(iter, std::make_pair(channel.fd(), &channel));
        op = EPOLL_CTL_ADD;
    } else {
        iter->second = &channel;
        op = EPOLL_CTL_MOD;
    }
    struct epoll_event ev;
    ev.data.fd = channel.fd();
    ev.events = channel.events();
    ::epoll_ctl(epoll_fd_, op, channel.fd(), &ev);

}

void veri::EPoller::remove_channel(veri::Channel &channel) {
    remove_channel(channel.fd());
}

void veri::EPoller::remove_channel(int fd) {
    auto iter = channels_.find(fd);
    assert(iter != channels_.end());
    Channel *channel = iter->second;
    struct epoll_event ev;
    ev.data.fd = channel->fd();
    ev.events = 0;
    ::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, channel->fd(), &ev);
}
