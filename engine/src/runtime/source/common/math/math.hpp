#ifndef ENGINE_RUNTIME_CORE_MATH_MATH
#define ENGINE_RUNTIME_CORE_MATH_MATH

#include <cfloat>
#include <cstdint>
#include <limits>

namespace taixu {

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static constexpr float FLOAT_INFINITY     = std::numeric_limits<float>::infinity();
static constexpr float FLOAT_INFINITY_NEG = std::numeric_limits<float>::infinity();
static constexpr float EPSILON_FLOAT      = std::numeric_limits<float>::epsilon();

static constexpr float F_DEG_2RAD = static_cast<float>(M_PI) / 180.0f;
static constexpr float F_RAD_2DEG = 180.0f / static_cast<float>(M_PI);
static constexpr float LOG2       = 1.4426950408889634f;

namespace literals {

    static constexpr uint8_t UC_MAX{255};

    constexpr uint8_t operator"" _uc(const uint64_t value) {
        if (value > UC_MAX) {
            return UC_MAX;
        }
        return static_cast<uint8_t>(value);
    }

}// namespace literals

}// namespace taixu

#endif /* ENGINE_RUNTIME_CORE_MATH_MATH */
