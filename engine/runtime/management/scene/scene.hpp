//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "management/ecs/ecs_coordinator.hpp"
#include "management/physics/physics_manager.hpp"
namespace taixu {
struct Scene {
    ECSCoordinator ecs_coordinator{};
    PhysicsManager physics_manager{};

    Scene() = default;
};
}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
