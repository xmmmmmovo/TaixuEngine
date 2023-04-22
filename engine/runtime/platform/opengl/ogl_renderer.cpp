//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"

namespace taixu {

void OGLRenderer::initialize(GLFWwindow *window) {
    _context->initialize(window);
}

void OGLRenderer::tick(float delta_time) { clear(); }

void OGLRenderer::clear() { _context->clear(); }

void OGLRenderer::clearSurface() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

}// namespace taixu