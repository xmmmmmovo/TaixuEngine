//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "gameplay/player/perspective_camera.hpp"
#include "management/ecs/components/camera/camera_component.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/components/rigid_body/rigid_body_component.hpp"
#include "management/ecs/components/transform/transform_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/ecs/object/game_object.hpp"
#include "management/graphics/render/texture_cube.hpp"
#include "management/input/input_system.hpp"
#include "management/physics/physics_manager.hpp"
#include "platform/opengl/ogl_shader.hpp"

#include "management/graphics/frontend/skybox.hpp"
#include "platform/opengl/ogl_texture_cube.hpp"
#include "resource/manager/asset_manager.hpp"

#include "skybox_frag.h"
#include "skybox_vert.h"

#include "frag_frag.h"
#include "vert_vert.h"
#include <memory>

namespace taixu {

class Scene {
private:
    using go_vec_t = std::vector<GameObject>;

    PROTOTYPE_ONLY_GETTER_CONST(private, go_vec_t, game_objs)

public:
    ECSCoordinator _ecs_coordinator{};
    PhysicsManager physics_manager{};

    Skybox                        _skybox{};
    std::unique_ptr<ITextureCube> _skybox_texture{nullptr};

    std::unique_ptr<PerspectiveCamera> _camera{
            std::make_unique<PerspectiveCamera>()};
    AssetManager *_asset_manager{nullptr};

    explicit Scene() {
        _ecs_coordinator.init();
        _ecs_coordinator.registerComponent<RenderableComponent>();
        _ecs_coordinator.registerComponent<TransformComponent>();

        physics_manager.init();
        _camera->Position = glm::vec3(0.0f, 4.0f, 20.0f);
        InputSystem::getInstance().registerEditorCallback(
                [this](float delta_time, WindowContext *const context) {
                    if (_camera == nullptr) { return; }

                    if (glfwGetKey(context->_window, GLFW_KEY_W) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::FORWARD,
                                                 delta_time);
                    }
                    if (glfwGetKey(context->_window, GLFW_KEY_S) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::BACKWARD,
                                                 delta_time);
                    }
                    if (glfwGetKey(context->_window, GLFW_KEY_A) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::LEFT,
                                                 delta_time);
                    }
                    if (glfwGetKey(context->_window, GLFW_KEY_D) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::RIGHT,
                                                 delta_time);
                    }

                    if (glfwGetKey(context->_window, GLFW_KEY_E) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::UP,
                                                 delta_time);
                    }
                    if (glfwGetKey(context->_window, GLFW_KEY_Q) ==
                        GLFW_PRESS) {
                        _camera->processKeyboard(CameraMovement::DOWN,
                                                 delta_time);
                    }

                    if (glfwGetKey(context->_window, GLFW_KEY_LEFT_SHIFT) ==
                        GLFW_PRESS) {
                        _camera->accelerate();
                    } else if (glfwGetKey(context->_window,
                                          GLFW_KEY_LEFT_SHIFT) ==
                               GLFW_RELEASE) {
                        _camera->decelerate();
                    }
                });
    }

    void fromWorld(JsonWorld *world) {
        if (world->json_levels.empty()) {
            spdlog::debug("There is no level in the project");
        }

        for (auto const &levels : world->json_levels) {
            auto parent_path = world->project_file_path;
            for (const auto &go : levels.json_game_objects) {
                auto entity = _ecs_coordinator.createEntity();

                auto renderable = RenderableComponent();
                auto model      = _asset_manager->loadModel(
                        parent_path, go.MeshComponent.obj_path);

                if (model->gpu_data == std::nullopt) {
                    transferCPUModelToGPU(model);
                }

                renderable.model    = model;
                renderable.visiable = go.MeshComponent.visiable;
                _ecs_coordinator.addComponent(
                        entity, std::forward<RenderableComponent>(renderable));

                auto trans =
                        TransformComponent(go.TransformComponent.position.vec3,
                                           go.TransformComponent.scale.vec3,
                                           go.TransformComponent.rotation.vec3);
                trans.makeTransformMatrix();
                _ecs_coordinator.addComponent(
                        entity, std::forward<TransformComponent &&>(trans));

                GameObject game_object{};
                game_object.entities.push_back(entity);

                _game_objs.push_back(game_object);
            }
        }

        auto const &global_render = world->global_json.render_global_json;

        _skybox_texture = std::make_unique<OGLTextureCube>(
                (world->project_file_path / global_render.posx).string(),
                (world->project_file_path / global_render.negx).string(),
                (world->project_file_path / global_render.posy).string(),
                (world->project_file_path / global_render.negy).string(),
                (world->project_file_path / global_render.posz).string(),
                (world->project_file_path / global_render.negz).string());
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
