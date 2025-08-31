#include "Algorithms.h"
#include "Logger.h"
#include "Storage.h"
#include <thread>
#include <chrono>

extern Logger logger;
extern Storage storage;

std::map<std::string, std::function<void(ThreadSafeQueue&, ThreadSafeQueue&)>> algorithmRegistry;

void registerAlgorithm(const std::string& name, std::function<void(ThreadSafeQueue&, ThreadSafeQueue&)> func) {
    algorithmRegistry[name] = func;
}

void runAlgorithm(ThreadSafeQueue& inputQueue, ThreadSafeQueue& outputQueue, const std::string& algorithmName) {
    while (true) {
        if (!inputQueue.empty()) {
            std::string key = inputQueue.pop();
            if (storage.exists(key)) {
                std::string viewData = storage.retrieve(key);
                logger.log(algorithmName + " started processing: " + key);
                std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate processing time
                std::string processedData = key + "_ProcessedBy_" + algorithmName;
                logger.log(algorithmName + " finished processing: " + processedData);
                outputQueue.push(processedData);
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Avoid busy waiting
        }
    }
}
