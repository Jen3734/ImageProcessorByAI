// Image Processor
// This program handles real-time streaming data, processes it asynchronously, and sends the processed data to RabbitMQ.

#include <iostream>
#include <thread>
#include <vector>
#include "ThreadSafeQueue.h"
#include "Algorithms.h"
#include "Logger.h"
#include "Storage.h"
#include "DataSplitter.h"

Logger logger;
Storage storage;

void streamData(ThreadSafeQueue& queue) {
    for (int i = 1; i <= 10; ++i) {
        std::string data = "Data_" + std::to_string(i);
        storage.store(data, "ViewContent_" + std::to_string(i));
        logger.log("Streaming: " + data);
        queue.push(data);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void sendToRabbitMQ(ThreadSafeQueue& queue) {
    while (!queue.empty()) {
        std::string data = queue.pop();
        std::string message = "{\"timestamp\": \"" + getCurrentTimestamp() + "\", \"message\": \"" + data + "\"}";
        logger.log("Sending to RabbitMQ: " + message);
    }
}

void processData(ThreadSafeQueue& inputQueue, ThreadSafeQueue& outputQueue, const std::string& algorithmName) {
    while (!inputQueue.empty()) {
        std::string key = inputQueue.pop();
        if (storage.exists(key)) {
            std::string viewData = storage.retrieve(key);
            logger.log(algorithmName + " started processing: " + key);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::string processedData = key + "_ProcessedBy_" + algorithmName;
            logger.log(algorithmName + " finished processing: " + processedData);
            outputQueue.push(processedData);
        }
    }
}

void handleStreamData(ThreadSafeQueue& queue, const std::string& rawData) {
    size_t chunkSize = 5; // Example chunk size
    std::vector<std::string> chunks = DataSplitter::splitData(rawData, chunkSize);
    for (const auto& chunk : chunks) {
        storage.store(chunk, "ChunkContent_" + chunk);
        logger.log("Handling stream chunk: " + chunk);
        queue.push(chunk);
    }
}

void consumerHandler(ThreadSafeQueue& inputQueue, ThreadSafeQueue& outputQueue, const std::string& algorithmName) {
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

int main() {
    ThreadSafeQueue inputQueue;
    ThreadSafeQueue outputQueue;

    // Register algorithms
    registerAlgorithm("Algorithm1", [](ThreadSafeQueue& input, ThreadSafeQueue& output) {
        processData(input, output, "Algorithm1");
    });

    registerAlgorithm("Algorithm2", [](ThreadSafeQueue& input, ThreadSafeQueue& output) {
        processData(input, output, "Algorithm2");
    });

    // Start streaming data
    std::thread producer(streamData, std::ref(inputQueue));

    // Start processing data with registered algorithms
    std::vector<std::thread> consumers;
    for (const auto& [name, func] : algorithmRegistry) {
        for (int i = 0; i < 2; ++i) { // Create multiple consumers per algorithm
            consumers.emplace_back(func, std::ref(inputQueue), std::ref(outputQueue));
        }
    }

    producer.join();
    for (auto& consumer : consumers) {
        consumer.join();
    }

    // Send processed data to RabbitMQ
    sendToRabbitMQ(outputQueue);

    return 0;
}
