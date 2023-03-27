#include <spdlog/spdlog.h>

#include "guid_genenrator.hpp"

namespace taixu
{
std::atomic<std::uint32_t> GUID_Generator::next_id{0};

std::uint32_t GUID_Generator::generate_new_guid() 
{
    std::atomic<std::uint32_t> new_id = next_id.load();
    next_id++;
    if (next_id >= INVALID_GUID) { spdlog::debug("GUID is overflow"); }
    return new_id;
}
}