//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "ogl_vertex_array.hpp"
#include "runtime/management/components/transform/transform_component.hpp"
#include <runtime/management/graphics/frontend/cube_renderable.hpp>
#include <runtime/management/graphics/frontend/lightsInfo.hpp>
#include <runtime/management/graphics/frontend/skybox.hpp>
#include <spdlog/spdlog.h>

namespace taixu {

constexpr std::array<float, 3> CLEAR_COLOR{0.1f, 0.1f, 0.1f};

void OGLRenderer::init() {
    this->_framebuffer = std::make_unique<OGLFrameBuffer>(
            IFrameBufferSpecification{FrameColorImageFormat::RGBA,
                                      FrameDepthImageFormat::DEPTH24STENCIL8});

    _matrices_ubo.bind();
    _matrices_ubo.setData(_matrices, 0);
    _matrices_ubo.unbind();

    _material_ubo.bind();
    _material_ubo.setData(_material, 1);
    _material_ubo.unbind();

    _lights_ubo.bind();
    _lights_ubo.setData(_lights, 2);
    _lights_ubo.unbind();

    _cube_renderable = &CubeRenderable::getInstance();
    _cube_renderable->init();
}

void OGLRenderer::update(float delta_time) {
    _framebuffer->bind();
    clear(CLEAR_COLOR);
    _framebuffer->unbind();
}

void OGLRenderer::clear(const std::array<float, 3>& color) {
    glClearColor(color[0], color[1], color[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::clearSurface() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


IFrameBuffer* OGLRenderer::getRenderFramebuffer() { return _framebuffer.get(); }

}// namespace taixu