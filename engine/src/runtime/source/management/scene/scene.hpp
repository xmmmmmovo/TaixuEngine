/**
 * @file scene.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include <management/ecs/core/ecs_types.hpp>
#include <management/ecs/ecs_coordinator.hpp>

#include "taixu/management/ecs/object/game_object.hpp"

namespace taixu {

/**
 * @brief 场景类
 * @details
 * Scene class
 * 用于管理场景中的物体
 * Used to manage objects in the scene
 * 以及场景中的各种系统
 * And various systems in the scene
 * 等效为World, 但是为了避免和json中的World混淆, 所以改名为Scene
 * 其中包含Level管理，一个scene可以有多个Level
 * 一个Level包含多个GameObject
 */
class Scene {

private:
    using go_vec_t = std::vector<GameObject>;

    PROTOTYPE_ONLY_GETTER(private, go_vec_t, game_objs)

public:
    ECSCoordinator _ecs_coordinator{};

    explicit Scene() {
        _ecs_coordinator.init();
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
