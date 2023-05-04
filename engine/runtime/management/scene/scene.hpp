//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/ecs/system/ecs_types.hpp"
#include "management/graphics/render/shader.hpp"
#include "management/physics/physics_manager.hpp"

namespace taixu {

class Scene {
public:
    ECSCoordinator          ecs_coordinator{};
    PhysicsManager          physics_manager{};
    IShaderProgram         *shader_program{nullptr};
    std::vector<EntityType> entities{};

    explicit Scene() {
        ecs_coordinator.init();
        ecs_coordinator.registerComponent<RenderableComponent>();
        physics_manager.init();
    }

    EntityType createEntity() {
        auto tmp_ent = ecs_coordinator.createEntity();
        entities.emplace_back(tmp_ent);
        return tmp_ent;
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
