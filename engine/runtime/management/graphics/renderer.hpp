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
#include "gameplay/player/perspective_camera.hpp"
#include "management/ecs/category/category.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/graphics/render/framebuffer.hpp"
#include "management/graphics/render/render_api.hpp"
#include "management/graphics/render/shader.hpp"
#include "management/graphics/render/texture2d.hpp"
#include "management/scene/scene.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

class IRenderer : private noncopyable {
public:
    virtual void init()                                   = 0;
    virtual void update()                                 = 0;
    virtual void clear(const std::array<float, 3> &color) = 0;
    virtual void clearSurface()                           = 0;

    virtual IFrameBuffer *getRenderFramebuffer() = 0;

    virtual void bindScene(Scene *scene) = 0;
};

class BaseRenderer : public IRenderer {
protected:
    Scene                          *_current_scene{nullptr};
    Category                       *_renderable_category{nullptr};
    static constexpr CategoryIdType _renderable_category_id =
            "renderable"_hash64;

    void bindScene(Scene *scene) override {
        _current_scene = scene;
        if (_current_scene != nullptr) {
            auto &coordinator = _current_scene->ecs_coordinator;
            _renderable_category =
                    coordinator.registerCategory(_renderable_category_id);
            {
                Signature signature;
                signature.set(
                        coordinator.getComponentType<RenderableComponent>());
                coordinator.setCategorySignature(_renderable_category_id,
                                                 signature);
            }
        } else {
            _renderable_category = nullptr;
        }
    };
};

}// namespace taixu

#endif//TAIXUENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDERER_HPP
