//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "spdlog/spdlog.h"

namespace taixu {

constexpr std::array<float, 3> CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                           0.9215686275f};

void OGLRenderer::initialize(GLFWwindow *window) {
    _context->initialize(window);
}

void OGLRenderer::tick(float delta_time) {
    _clock.update();
    _context->getRenderFramebuffer()->bind();
    clear(CLEAR_COLOR);
    _context->getRenderFramebuffer()->unbind();
}

void OGLRenderer::clear(const std::array<float, 3> &color) {
    glClearColor(color[0], color[1], color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::clearSurface() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

}// namespace taixu