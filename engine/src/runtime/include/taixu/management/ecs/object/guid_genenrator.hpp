#ifndef TAIXUENGINE_GUID_GENERATOR
#define TAIXUENGINE_GUID_GENERATOR

#include <atomic>
#include <cstdint>
#include <limits>

namespace taixu {

constexpr std::uint32_t INVALID_GUID = std::numeric_limits<std::uint32_t>::max();
using GUID                           = std::uint32_t;

class GuidGenerator {
public:
    static GUID generateNewGuid();

private:
    static std::atomic<GUID> _next_id;
};

}// namespace taixu

#endif /* TAIXUENGINE_GUID_GENERATOR */
