#include "DataSplitter.h"

std::vector<std::string> DataSplitter::splitData(const std::string& rawData, size_t chunkSize) {
    std::vector<std::string> chunks;
    for (size_t i = 0; i < rawData.size(); i += chunkSize) {
        chunks.push_back(rawData.substr(i, chunkSize));
    }
    return chunks;
}
