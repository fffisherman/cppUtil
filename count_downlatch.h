#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include "noncopyable.h"

class CountDownLatch : noncopyable{
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();
    int getCount() const;
private:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};