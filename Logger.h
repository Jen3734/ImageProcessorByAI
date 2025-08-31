#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

class Logger {
private:
    std::mutex mtx;

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::ostringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

public:
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << message << std::endl;
    }

    void logWithTimestamp(const std::string& message) {
        std::string timestampedMessage = "[" + getCurrentTimestamp() + "] " + message;
        log(timestampedMessage);
    }
};

#endif // LOGGER_H
