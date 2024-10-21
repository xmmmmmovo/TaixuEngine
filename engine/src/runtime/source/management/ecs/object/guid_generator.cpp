
#include <taixu/common/log/logger.hpp>
#include <taixu/management/ecs/object/guid_genenrator.hpp>

namespace taixu {

std::atomic<GUID> GuidGenerator::_next_id{0};

GUID GuidGenerator::generateNewGuid() {
    std::atomic const new_id = _next_id.load();
    ++_next_id;
    if (_next_id >= INVALID_GUID) {
        FATAL_LOG("GUID is overflow");
    }
    return new_id;
}

}// namespace taixu
