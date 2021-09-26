#pragma once

#include <string>
#include <vector>
#include <map>

#include "event_loop.h"
#include "noncopyable.h"

class Channel;
class Timestamp;

class Poller : public noncopyable {
public:
    typedef std::vector<Channel> ChannelList;
    Poller(EventLoop* loop);
    virtual ~Poller();

    virtual Timestamp poll(int timeout, ChannelList& active_channels) = 0;

    virtual void updateChannel(ChannelList* channel) = 0;

    virtual void remveChannel(ChannelList* channel) = 0;

    virtual bool hasChannel(Channel* Channel) const;

    void assertInLoopThread() const {};

protected:
    typedef std::map<int, Channel*> ChannelMap;
    ChannelMap channels_;

private:
    EventLoop* owner_loop_;
};