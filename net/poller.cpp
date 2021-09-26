#include "poller.h"
#include "event_loop.h" 

Poller::Poller(EventLoop* loop):
    owner_loop_(loop) {
}

Poller::~Poller(){}

bool Poller::hasChannel(Channel* channel) const {
    assertInLoopThread();
    auto it = channels_.find(channel->fd());
    return it !=channels_.end() && it->second == channel;
}