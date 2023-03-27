#ifndef TAIXUENGINE_GUID_GENERATOR
#define TAIXUENGINE_GUID_GENERATOR

#include <atomic>
#include <cstdint>
#include <limits>

namespace taixu
{
constexpr std::uint32_t INVALID_GUID = std::numeric_limits<std::uint32_t>::max();
class GUID_Generator {
public:
    static std::uint32_t generate_new_guid();

private:
    static std::atomic<std::uint32_t> next_id;
};

}

#endif /* TAIXUENGINE_GUID_GENERATOR */
