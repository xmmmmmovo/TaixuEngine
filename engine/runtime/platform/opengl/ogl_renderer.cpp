//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"

namespace taixu {
void OGLRenderer::initialize() {}

void OGLRenderer::tick(float delta_time) {}

void OGLRenderer::clear() {}

IGraphicsContext *OGLRenderer::getContext() { return this->context.get(); }
}// namespace taixu