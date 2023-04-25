//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_RENDERER_HPP
#define TAIXUENGINE_RENDERER_HPP

#include <memory>
#include <vector>

#include "backends/imgui_impl_glfw.h"
#include "core/base/clock.hpp"
#include "core/base/noncopyable.hpp"
#include "frag_frag.h"
#include "graphics/render/framebuffer.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "platform/opengl/ogl_shader.hpp"

namespace taixu {

class IRenderer : private noncopyable {
public:
    virtual void initialize()                             = 0;
    virtual void tick(float delta_time = 0.03333)         = 0;
    virtual void clear(const std::array<float, 3> &color) = 0;
    virtual void clearSurface()                           = 0;

    virtual IFrameBuffer *getRenderFramebuffer() = 0;
};

class BaseRenderer : public IRenderer {

protected:
    Clock _clock{};
};

}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
