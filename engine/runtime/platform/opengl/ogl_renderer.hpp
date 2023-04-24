//
// Created by xmmmmmovo on 2023/4/6.
//

#ifndef TAIXUENGINE_OGL_RENDERER_HPP
#define TAIXUENGINE_OGL_RENDERER_HPP

#include "graphics/renderer.hpp"
#include "ogl_frameBuffer.hpp"
#include <memory>

namespace taixu {

class OGLRenderer : public BaseRenderer {
private:
    std::unique_ptr<OGLFrameBuffer> _framebuffer{nullptr};

public:
    OGLRenderer() = default;

    void initialize() override;

    void tick(float delta_time) override;
    void clear(const std::array<float, 3> &color) override;

    void clearSurface() override;

    IFrameBuffer *getRenderFramebuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_RENDERER_HPP
