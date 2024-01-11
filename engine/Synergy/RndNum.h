#include <random>
#include "glm/glm.hpp"

class StaticRandom {
public:
    // Integer in range [min, max]
    static int Int(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    // Float in range [min, max]
    static float Float(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }

    // Float in range [0, 1]
    static float UnitFloat() {
        return Float(0.0f, 1.0f);
    }

    // glm::vec3 in range [min, max]
    static glm::vec3 Vec3(const glm::vec3& min, const glm::vec3& max) {
        return glm::vec3(Float(min.x, max.x), Float(min.y, max.y), Float(min.z, max.z));
    }

    // glm::vec4 in range [min, max]
    static glm::vec4 Vec4(const glm::vec4& min, const glm::vec4& max) {
        return glm::vec4(Float(min.x, max.x), Float(min.y, max.y), Float(min.z, max.z), Float(min.w, max.w));
    }

private:
    static std::mt19937 generator;
};

// Initialize the static member
std::mt19937 StaticRandom::generator(std::random_device{}());