#pragma once
#include <string>
#include <sstream>

class StringHelper {
public:
    static std::string AddToString(const std::string& original, int number) {
        return original + std::to_string(number);
    }

    static std::string AddToString(const std::string& original, float number) {
        std::ostringstream oss;
        oss << number;
        return original + oss.str();
    }

    static std::string AddToString(const std::string& original, double number) {
        std::ostringstream oss;
        oss << number;
        return original + oss.str();
    }
};