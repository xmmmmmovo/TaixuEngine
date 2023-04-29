#ifndef TAIXUENGINE_GAME_OBJECT
#define TAIXUENGINE_GAME_OBJECT

#include <filesystem>

#include "core/base/macro.hpp"
#include "guid_genenrator.hpp"

namespace taixu {

class GameObject {
    PROTOTYPE_DFT(private, GUID, guid, GuidGenerator::generateNewGuid());
};

}// namespace taixu
#endif /* TAIXUENGINE_GAME_OBJECT */
