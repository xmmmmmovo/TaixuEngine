//
// Created by xmmmmmovo on 2023/5/13.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP

#include "core/base/macro.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/object/guid_genenrator.hpp"

namespace taixu {
class GameObject {
    PROTOTYPE_DFT(private, GUID, guid, GuidGenerator::generateNewGuid());
    PROTOTYPE_DFT(private, std::string, name, "NoName");

public:
    std::vector<Entity> entities;
};
}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_OBJECT_GAME_OBJECT_HPP
