#pragma once

#include <functional>
#include <memory>
#include "noncopyable.h"

class EventLoop;
class Timestamp;

class Channel : public noncopyable {
public:
    typedef std::function<void()> EventCallback;
    typedef std::function<void(Timestamp)> ReadEventCallback;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void handleEvent(Timestamp receiveTime);
    void setReadCallBack(ReadEventCallback cb) {
        read_event_back_ = cb;
    }

    void setWriteCallBack(EventCallback cb) {
        write_call_back_ = cb;
    }

    void setCloseCallBack(EventCallback cb) {
        close_call_back_ = cb;
    }

    void setErrorCallBack(EventCallback cb) {
        error_call_back_ = cb;
    }

    void tie(const std::shared_ptr<void>&);

    int fd() const { return fd_; }
    int events()const { return event_;}
    void setEvents(int event) { event_ = event;}
    void setReturnEvent(int event) { return_event_ = event;}
    bool isNoneEvent() const { return event_ == KNoneEvent;}
    void enableReading() {event_ |= KReadEvent; update();}
    void enableWriting() {event_ |= KWriteEvent; update();}
    void disableReading() {event_ &= ~KReadEvent; update();}
    void disableWriting() {event_ &= ~KWriteEvent; update();}

    bool isWriting() const { return event_ & KWriteEvent;}
    bool isReading() const { return event_  & KReadEvent;}

    int index() {return index_;}
    void set_index(int index) {index_ = index;}

    std::string eventToString() const;
    std::string reventToString() const;

    void doNotLogHup() {log_hup_ = false;}
    EventLoop* ownerLoop() { return loop_;}
    void remove();

private:
    static std::string eventToString(int fd, int ev);
    void update();
    void handlingEventWithGuard(Timestamp receive_time);

    // 无事件、读写事件
    static const int KNoneEvent;
    static const int KReadEvent;
    static const int KWriteEvent;

    int event_; //注册的事件
    int return_event_;    //返回的事件
    const int fd_;
    int index_;
    bool log_hup_;

    EventLoop* loop_;
    std::weak_ptr<void> tie_;
    bool tied_;
    bool event_handling_;
    bool added_to_loop_;
    
    ReadEventCallback read_event_back_;
    EventCallback write_call_back_;
    EventCallback close_call_back_;
    EventCallback error_call_back_;
};