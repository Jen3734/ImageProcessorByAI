#ifndef RABBITMQDRIVER_H
#define RABBITMQDRIVER_H

#include "ThreadSafeQueue.h"
#include "Logger.h"
#include <string>

class RabbitMQDriver {
private:
    Logger& logger;

public:
    RabbitMQDriver(Logger& log) : logger(log) {}

    void receiveStream(ThreadSafeQueue& queue, const std::string& data) {
        logger.log("RabbitMQ received: " + data);
        queue.push(data);
    }
};

#endif // RABBITMQDRIVER_H
