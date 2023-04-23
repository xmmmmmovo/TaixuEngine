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
#include "graphics/render/model.hpp"
#include "graphics/render/perspective_camera.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render/shader.hpp"
#include "graphics/render/texture.hpp"
#include "graphics/render_context.hpp"
#include "platform/opengl/ogl_context.hpp"
#include "platform/opengl/ogl_shader.hpp"
#include "render_context.hpp"

namespace taixu {

class AbstractRenderer : private noncopyable {
public:
    virtual void initialize()   = 0;
    virtual void tick(float delta_time = 0.03333) = 0;
    virtual void clear(const std::array<float, 3> &color) = 0;
    virtual void clearSurface()                   = 0;

    virtual IGraphicsContext *getContext() = 0;
};

template<typename Context = IGraphicsContext>
class BaseRenderer : public AbstractRenderer {
protected:
    Clock                    _clock{};
    std::unique_ptr<Context> _context{nullptr};

public:
    IGraphicsContext *getContext() override { return _context.get(); };
};

}// namespace taixu

#endif//TAIXUENGINE_RENDERER_HPP
