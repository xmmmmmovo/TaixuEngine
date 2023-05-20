//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDERER_HPP
#define TAIXUENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDERER_HPP

#include <memory>
#include <vector>

#include <backends/imgui_impl_glfw.h>

#include "core/base/clock.hpp"
#include "core/base/hash.hpp"
#include "core/base/noncopyable.hpp"
#include "gameplay/player/camera/euler_camera.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/components/rigid_body/rigid_body_component.hpp"
#include "management/ecs/components/animation/skeleton_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/system/system.hpp"
#include "management/graphics/frontend/lightsInfo.hpp"
#include "management/graphics/frontend/materialInfo.hpp"
#include "management/graphics/frontend/matrices.hpp"
#include "management/graphics/render/framebuffer.hpp"
#include "management/graphics/render/render_api.hpp"
#include "management/graphics/render/shader.hpp"
#include "management/graphics/render/texture_2d.hpp"
#include "management/scene/scene.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

class AbstractRenderer : private noncopyable {
    PROTOTYPE_DFT(protected, bool, move_mode, false)

public:
    virtual void init()                                   = 0;
    virtual void update(float delta_time)                 = 0;
    virtual void clear(const std::array<float, 3> &color) = 0;
    virtual void clearSurface()                           = 0;

    virtual IFrameBuffer *getRenderFramebuffer() = 0;

    virtual void bindScene(Scene *scene) = 0;
};

class BaseRenderer : public AbstractRenderer {

protected:
    Scene  *_current_scene{nullptr};
    System *_renderable_system{nullptr};

    static constexpr SystemIdType RENDERABLE_SYSTEM_ID = "renderable"_hash64;

    std::unique_ptr<IShaderProgram> _render_shader{nullptr};
    std::unique_ptr<IShaderProgram> _skybox_shader{nullptr};
    std::unique_ptr<IShaderProgram> _animation_shader{nullptr};

    Matrices _matrices{};

    float _last_mouse_x{0.0f}, _last_mouse_y{0.0f};

    void updateCamera(float delta_time) {
        if (_current_scene->_camera != nullptr) {
            auto const &inputsystem = InputSystem::getInstance();

            if (inputsystem.getInputState(GLFW_KEY_W)) {
                _current_scene->_camera->processKeyboard(
                        CameraMovement::FORWARD, delta_time);
            }
            if (inputsystem.getInputState(GLFW_KEY_S)) {
                _current_scene->_camera->processKeyboard(
                        CameraMovement::BACKWARD, delta_time);
            }
            if (inputsystem.getInputState(GLFW_KEY_A)) {
                _current_scene->_camera->processKeyboard(CameraMovement::LEFT,
                                                         delta_time);
            }
            if (inputsystem.getInputState(GLFW_KEY_D)) {
                _current_scene->_camera->processKeyboard(CameraMovement::RIGHT,
                                                         delta_time);
            }

            if (inputsystem.getInputState(GLFW_KEY_E)) {
                _current_scene->_camera->processKeyboard(CameraMovement::UP,
                                                         delta_time);
            }
            if (inputsystem.getInputState(GLFW_KEY_Q)) {
                _current_scene->_camera->processKeyboard(CameraMovement::DOWN,
                                                         delta_time);
            }

            if (inputsystem.getInputState(GLFW_KEY_LEFT_SHIFT)) {
                _current_scene->_camera->accelerate();
            } else {
                _current_scene->_camera->decelerate();
            }

            if (_move_mode) {
                _current_scene->_camera->processMouseMovement(
                        inputsystem.state().mouse_x - _last_mouse_x,
                        _last_mouse_y - inputsystem.state().mouse_y);
            }
            _last_mouse_x = inputsystem.state().mouse_x;
            _last_mouse_y = inputsystem.state().mouse_y;

            if (inputsystem.state().was_mouse_scrolling) {
                _current_scene->_camera->processMouseScroll(
                        inputsystem.state().mouse_scroll_offset_y);
            }
        }
    }

    void bindScene(Scene *scene) override {
        _current_scene = scene;
        if (_current_scene != nullptr) {
            auto &coordinator = _current_scene->_ecs_coordinator;
            _renderable_system =
                    coordinator.registerSystem(RENDERABLE_SYSTEM_ID);
            {
                Signature render_signature;
                render_signature.set(
                        coordinator.getComponentType<RenderableComponent>());

                render_signature.set(
                        coordinator.getComponentType<TransformComponent>());
                coordinator.setsystemSignature(RENDERABLE_SYSTEM_ID,
                                               render_signature);
                
                render_signature.set(
                        coordinator.getComponentType<LightComponent>());
                coordinator.setsystemSignature(RENDERABLE_SYSTEM_ID,
                                               render_signature);
                                            
                render_signature.set(
                        coordinator.getComponentType<SkeletonComponent>());
                coordinator.setsystemSignature(RENDERABLE_SYSTEM_ID,
                                               render_signature);                                  
            }
        } else {
            _renderable_system = nullptr;
        }
    };
};

}// namespace taixu

#endif//TAIXUENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDERER_HPP
