#include "Storage.h"
#include <stdexcept>

void Storage::store(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mtx);
    dataStorage[key] = value;
}

std::string Storage::retrieve(const std::string& key) {
    std::lock_guard<std::mutex> lock(mtx);
    if (dataStorage.find(key) != dataStorage.end()) {
        return dataStorage[key];
    }
    throw std::runtime_error("Key not found in storage");
}

bool Storage::exists(const std::string& key) {
    std::lock_guard<std::mutex> lock(mtx);
    return dataStorage.find(key) != dataStorage.end();
}
