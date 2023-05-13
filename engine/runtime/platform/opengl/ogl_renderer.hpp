//
// Created by xmmmmmovo on 2023/4/6.
//

#ifndef TAIXUENGINE_OGL_RENDERER_HPP
#define TAIXUENGINE_OGL_RENDERER_HPP

#include "management/graphics/renderer.hpp"
#include "ogl_frameBuffer.hpp"
#include <memory>

namespace taixu {

class OGLRenderer : public BaseRenderer {
private:
    std::unique_ptr<OGLFrameBuffer> _framebuffer{nullptr};

public:
    OGLRenderer() = default;

    void init() override;

    void update() override;
    void clear(const std::array<float, 3> &color) override;

    void clearSurface() override;

    void bindShader();
    glm::mat4 transform{glm::mat4(1.0f)};

    IFrameBuffer *getRenderFramebuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_RENDERER_HPP
