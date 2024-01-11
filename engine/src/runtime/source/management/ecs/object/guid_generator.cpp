
#include "management/ecs/object/guid_genenrator.hpp"
#include <common/base/macro.hpp>
#include <common/log/logger.hpp>

namespace taixu {

std::atomic<GUID> GuidGenerator::_next_id{0};

GUID GuidGenerator::generateNewGuid() {
    std::atomic<std::uint32_t> const new_id = _next_id.load();
    ++_next_id;
    if (_next_id >= INVALID_GUID) { FATAL_LOG("GUID is overflow"); }
    return new_id;
}

}// namespace taixu