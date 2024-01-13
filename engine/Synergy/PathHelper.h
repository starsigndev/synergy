#pragma once
#include <string>
#include <algorithm>

class PathHelper {
public:
    // Extracts the directory path from a full file path
    static std::string ExtractPath(const std::string& filePath) {
        size_t lastSlash = filePath.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            return filePath.substr(0, lastSlash + 1);
        }
        return ""; // No path found
    }

    // Extracts the file name from a full file path
    static std::string ExtractFileName(const std::string& filePath) {
        size_t lastSlash = filePath.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            return filePath.substr(lastSlash + 1);
        }
        return filePath; // No path, return the entire string
    }
};