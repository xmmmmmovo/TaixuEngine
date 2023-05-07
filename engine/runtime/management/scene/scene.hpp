//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "gameplay/player/perspective_camera.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/graphics/render/shader.hpp"
#include "management/input/input_system.hpp"
#include "management/physics/physics_manager.hpp"
#include "platform/opengl/ogl_shader.hpp"

#include "frag_frag.h"
#include "vert_vert.h"

namespace taixu {

class Scene {
public:
    ECSCoordinator                  ecs_coordinator{};
    PhysicsManager                  physics_manager{};
    std::unique_ptr<IShaderProgram> shader_program{
            std::make_unique<OGLShaderProgram>(VERT_VERT, FRAG_FRAG)};

    std::unique_ptr<PerspectiveCamera> _camera{
            std::make_unique<PerspectiveCamera>()};

    explicit Scene() {
        ecs_coordinator.init();
        ecs_coordinator.registerComponent<RenderableComponent>();

        physics_manager.init();

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
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
