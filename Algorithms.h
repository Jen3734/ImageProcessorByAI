#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "ThreadSafeQueue.h"
#include <map>
#include <functional>
#include <string>

extern std::map<std::string, std::function<void(ThreadSafeQueue&, ThreadSafeQueue&)>> algorithmRegistry;

void registerAlgorithm(const std::string& name, std::function<void(ThreadSafeQueue&, ThreadSafeQueue&)> func);
void runAlgorithm(ThreadSafeQueue& inputQueue, ThreadSafeQueue& outputQueue, const std::string& algorithmName);

#endif // ALGORITHMS_H
