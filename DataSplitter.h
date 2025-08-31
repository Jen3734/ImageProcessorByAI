#ifndef DATASPLITTER_H
#define DATASPLITTER_H

#include <vector>
#include <string>

class DataSplitter {
public:
    static std::vector<std::string> splitData(const std::string& rawData, size_t chunkSize);
};

#endif // DATASPLITTER_H
