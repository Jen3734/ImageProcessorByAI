#ifndef STORAGE_H
#define STORAGE_H

#include <unordered_map>
#include <string>
#include <mutex>

class Storage {
private:
    std::unordered_map<std::string, std::string> dataStorage;
    std::mutex mtx;

public:
    void store(const std::string& key, const std::string& value);
    std::string retrieve(const std::string& key);
    bool exists(const std::string& key);
};

#endif // STORAGE_H
