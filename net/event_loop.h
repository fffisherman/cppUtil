#pragma once

class EventLoop{
public:

    bool isInLoopThread();
    bool hasChannel(Channel* channel);

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
};