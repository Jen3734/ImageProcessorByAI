#include "ThreadSafeQueue.h"

void ThreadSafeQueue::push(const std::string& data) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(data);
    cv.notify_one();
}

std::string ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return !queue.empty(); });
    std::string data = queue.front();
    queue.pop();
    return data;
}

bool ThreadSafeQueue::empty() {
    std::lock_guard<std::mutex> lock(mtx);
    return queue.empty();
}
