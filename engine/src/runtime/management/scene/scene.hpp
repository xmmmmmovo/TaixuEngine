//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "runtime/gameplay/player/camera/euler_camera.hpp"
#include "runtime/management/components/camera/camera_component.hpp"
#include "runtime/management/components/renderable/renderable_component.hpp"
#include "runtime/management/components/transform/transform_component.hpp"

#include <runtime/management/ecs/core/ecs_types.hpp>
#include <runtime/management/ecs/ecs_coordinator.hpp>
#include <runtime/management/ecs/object/game_object.hpp>
#include <runtime/management/graphics/render/texture_cube.hpp>
#include <runtime/management/input/input_system.hpp>

#include <runtime/platform/opengl/ogl_shader.hpp>

#include <runtime/management/graphics/frontend/skybox.hpp>
#include <runtime/management/graphics/render/texture_2d.hpp>
#include <runtime/platform/opengl/ogl_texture2d.hpp>
#include <runtime/platform/opengl/ogl_texture_cube.hpp>
#include <runtime/resource/manager/asset_manager.hpp>

#include "skybox_frag.h"
#include "skybox_vert.h"

#include "frag_frag.h"
#include "vert_vert.h"

#include "skeleton_frag.h"
#include "skeleton_vert.h"

#include <memory>

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

    std::unique_ptr<ITextureCube> _skybox_texture{nullptr};

    std::unique_ptr<EulerCamera> _camera{
            std::make_unique<EulerCamera>(glm::vec3(0.0f, 2.0f, 10.5f))};

    explicit Scene() {
        _ecs_coordinator.init();
        _ecs_coordinator.registerComponent<RenderableComponent>();
        _ecs_coordinator.registerComponent<TransformComponent>();
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
