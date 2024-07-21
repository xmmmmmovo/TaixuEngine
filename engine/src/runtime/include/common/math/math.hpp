#ifndef ENGINE_RUNTIME_CORE_MATH_MATH
#define ENGINE_RUNTIME_CORE_MATH_MATH

#include <cfloat>
#include <limits>

namespace taixu {

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static constexpr float FLOAT_INFINITY     = std::numeric_limits<float>::infinity();
static constexpr float FLOAT_INFINITY_NEG = std::numeric_limits<float>::infinity();
static constexpr float EPSILON_FLOAT      = std::numeric_limits<float>::epsilon();

static constexpr float F_DEG_2RAD = M_PI / 180.0f;
static constexpr float F_RAD_2DEG = 180.0f / M_PI;
static constexpr float LOG2       = 1.4426950408889634f;

}// namespace taixu

#endif /* ENGINE_RUNTIME_CORE_MATH_MATH */
