//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "glm/fwd.hpp"
#include "ogl_vertex_array.hpp"
#include "spdlog/spdlog.h"

namespace taixu {

constexpr std::array<float, 3> CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                           0.9215686275f};

void OGLRenderer::init() {
    this->_framebuffer = std::make_unique<OGLFrameBuffer>(
            IFrameBufferSpecification{FrameColorImageFormat::RGBA,
                                      FrameDepthImageFormat::DEPTH24STENCIL8});

    _matrices_ubo.bind();
    _matrices_ubo.setData(_matrices, 0);
    _matrices_ubo.unbind();
}

void OGLRenderer::update() {
    _framebuffer->bind();
    clear(CLEAR_COLOR);

    if (_current_scene != nullptr) {

        _matrices.projection = _current_scene->_camera->getProjectionMatrix();
        _matrices.view       = _current_scene->_camera->getViewMatrix();
        _matrices.vp         = _matrices.projection * _matrices.view;
        _matrices_ubo.bind();
        _matrices_ubo.updateData(_matrices, 0);
        _matrices_ubo.unbind();

        _current_scene->shader_program->use();
        for (auto const &entity : _renderable_system->entities()) {
            auto const &renderable =
                    _current_scene->_ecs_coordinator
                            .getComponent<RenderableComponent>(entity);
            if (renderable.visiable) {
                auto const &trans =
                        _current_scene->_ecs_coordinator
                                .getComponent<TransformComponent>(entity);
                _current_scene->shader_program->set_uniform("model",
                                                            trans.transform);
                for (auto &mesh : renderable.model->gpu_data.value().meshes) {
                    mesh.vao->draw(mesh.index_count);
                }
            }
        }
    }

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