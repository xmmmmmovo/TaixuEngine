//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "spdlog/spdlog.h"

namespace taixu {

constexpr std::array<float, 3> CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                           0.9215686275f};

void OGLRenderer::init() {
    this->_framebuffer = std::make_unique<OGLFrameBuffer>(
            IFrameBufferSpecification{FrameColorImageFormat::RGBA,
                                      FrameDepthImageFormat::DEPTH24STENCIL8});
}

void OGLRenderer::update() {
    _clock.update();
    _framebuffer->bind();
    clear(CLEAR_COLOR);
    if (_current_scene != nullptr) {}
    _framebuffer->unbind();
}

void OGLRenderer::clear(const std::array<float, 3> &color) {
    glClearColor(color[0], color[1], color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::clearSurface() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

IFrameBuffer *OGLRenderer::getRenderFramebuffer() { return _framebuffer.get(); }

}// namespace taixu