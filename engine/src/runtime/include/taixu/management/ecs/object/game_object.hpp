//
// Created by xmmmmmovo on 2023/5/13.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP

#include "common/hal/tx_string.hpp"
#include <taixu/common/base/macro.hpp>
#include <taixu/management/ecs/object/guid_genenrator.hpp>

namespace taixu {
class GameObject {
    PROTOTYPE_DFT(private, GUID, guid, GuidGenerator::generateNewGuid());
    PROTOTYPE_DFT(private, tx_string, name, "NoName");
    PROTOTYPE_DFT(private, bool, active, true);
    PROTOTYPE_DFT(private, Entity, entity, true);
};
}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP
