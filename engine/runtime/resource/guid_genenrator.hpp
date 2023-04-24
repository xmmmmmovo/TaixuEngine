#ifndef TAIXUENGINE_GUID_GENERATOR
#define TAIXUENGINE_GUID_GENERATOR

#include <atomic>
#include <cstdint>
#include <limits>

namespace taixu {
constexpr std::uint32_t INVALID_GUID =
        std::numeric_limits<std::uint32_t>::max();
class GuidGenerator {
public:
    static std::uint32_t generateNewGuid();

private:
    static std::atomic<std::uint32_t> _next_id;
};

}// namespace taixu

#endif /* TAIXUENGINE_GUID_GENERATOR */
