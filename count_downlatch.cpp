#include "count_downlatch.h"

CountDownLatch::CountDownLatch(int count)
 : count_(count)
 , mutex_()
 , cv_() {
}

void CountDownLatch::wait() {
    std::unique_lock lock(mutex_);
       cv_.wait(lock, count_ > 0);
}
void CountDownLatch::countDown() {
    std::unique_lock lock(mutex_);
    --count_;
    if (count_ == 0) {
        cv_.notify_all();
    }
}
int CountDownLatch::getCount() const {
    std::unique_lock lock(mutex_);
    return count_;
}