#include <deque>
#include <assert.h>
#include <mutex>
#include <condition_variable>
#include "noncopyable.h"

template <class T>
class BlockingQueu : noncopyable {
public:
    BlockingQueu(): mutex_(), queue_(), not_empty_cv_() {        
    }

    void put(const T&x) {
        std::unique_lock lock(mutex_);
        queue_.push_back(x);
        not_empty_cv_.notify_all();
    }

    T take() {
        std::unique_lock lock(mutex_);
        not_empty_cv_.wait(lock, queue_.empty() == false);
        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        return front;
    }

    size_t size() const {
        std::unique_lock lock(mutex_);
        return queue_.size();
    }

private:
    std::mutex mutex_;
    std::condition_variable not_empty_cv_;
    std::deque<T> queue_;
};
