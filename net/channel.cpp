#include "channel.h"

#include <sstream>
#include <poll.h>
#include <assert.h>

#include "event_loop.h"
#include "time_stamp.h"

const int Channel::KNoneEvent = 0;
const int Channel::KReadEvent = POLLIN | POLLPRI;
const int Channel::KWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd) 
    :loop_(loop),
    fd_(fd),
    event_(0),
    return_event_(0),
    index_(-1),
    log_hup_(true),
    tied_(false),
    event_handling_(false),
    added_to_loop_(false) {
}

Channel::~Channel() {
    assert(!event_handling_);
    assert(!added_to_loop_);
    if (loop_->isInLoopThread()) {
        assert(!loop_->hasChannel(this));
    }
}

void Channel::tie(const std::shared_ptr<void>& obj) {
    tie_ = obj;
    tied_ = true;
}

void Channel::update() {
    added_to_loop_ = true;
    loop_->updateChannel(this);
}

void Channel::remove() {
    assert(isNoneEvent());
    added_to_loop_ = false;
    loop_->removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime) {
    std::shared_ptr<void> guard;
    if (tied_) {
        guard = tie_.lock();
        if (guard)
        {
            handlingEventWithGuard(receiveTime);
        }
    } else {
        handlingEventWithGuard(receiveTime);
    }
}

void Channel::handlingEventWithGuard(Timestamp receiveTime) {
    event_handling_ = true;
    if ((return_event_ & POLLHUP) && (!return_event_ & POLLIN)) {
        if (close_call_back_) {
            close_call_back_();
        }
    } else if (return_event_ & POLLNVAL) {
        // nothing
    } else if (return_event_ & (POLLERR | POLLNVAL)) {
        if (error_call_back_) {
            error_call_back_();
        }
    } else if (return_event_ & (POLLIN | POLLPRI | POLLRDHUP)) {
        if (read_event_back_) {
            read_event_back_(receiveTime);
        }
    } else if (return_event_ & POLLOUT) {
        if (write_call_back_) {
            write_call_back_();
        }
    }
    event_handling_ = false;
}

std::string Channel::reventToString() const {
    return eventToString(fd_, return_event_);
}

std::string Channel::eventToString() const {
    return eventToString(fd_, return_event_);
}

std::string Channel::eventToString(int fd, int ev) {
    std::ostringstream oss;
    oss << fd << ": ";
    if (ev & POLLIN)
        oss << "IN ";
    if (ev & POLLPRI)
        oss << "PRI ";
    if (ev & POLLOUT)
        oss << "OUT ";
    if (ev & POLLHUP)
        oss << "HUP ";
    if (ev & POLLRDHUP)
        oss << "RDHUP ";
    if (ev & POLLERR)
        oss << "ERR ";
    if (ev & POLLNVAL)
        oss << "NVAL ";

    return oss.str();
}