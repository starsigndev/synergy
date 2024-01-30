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

    static std::string removeFileExtension(const std::string& path) {
        // Find the last occurrence of the dot (.)
        size_t dotPosition = path.find_last_of('.');

        // If a dot is found and it is not the first character, remove the extension
        if (dotPosition != std::string::npos && dotPosition > 0) {
            return path.substr(0, dotPosition);
        }
        else {
            // If no dot is found or it is the first character, return the original path
            return path;
        }
    }
    static std::string getFileExtension(const std::string& path) {
        // Find the last occurrence of the dot (.)
        size_t dotPosition = path.find_last_of('.');

        // If a dot is found and it is not the last character, extract the extension
        if (dotPosition != std::string::npos && dotPosition < path.length() - 1) {
            return path.substr(dotPosition + 1);
        }
        else {
            // If no dot is found or it is the last character, return an empty string
            return "";
        }
    }

};