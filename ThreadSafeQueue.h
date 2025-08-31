#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

class ThreadSafeQueue {
private:
    std::queue<std::string> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    void push(const std::string& data);
    std::string pop();
    bool empty();
};

#endif // THREADSAFEQUEUE_H
