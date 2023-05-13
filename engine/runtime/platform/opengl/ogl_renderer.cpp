//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "glm/fwd.hpp"
#include "ogl_vertexArray.hpp"
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
    _framebuffer->bind();
    clear(CLEAR_COLOR);
    if (_current_scene != nullptr) {

        for (auto const &entity : _renderable_system->entities()) {
            
            auto const &renderable =
                    _current_scene->ecs_coordinator
                            .getComponent<RenderableComponent>(entity);
            if(renderable.visiable == true)
            {
                auto const &trans = _current_scene->ecs_coordinator
                                 .getComponent<TransformComponent>(entity);
                transform = trans.transform;
            
                bindShader();
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

void OGLRenderer::bindShader() {
    if (_current_scene != nullptr) {
        _current_scene->shader_program->use();
        glm::mat4 const p    = _current_scene->_camera->getProjectionMatrix();
        glm::mat4 const v    = _current_scene->_camera->getViewMatrix();
        glm::mat4       m    = transform;
        m                    = glm::translate(m, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat3 const mv33 = glm::mat3(v * m);
        glm::mat4 const mvp  = p * v * m;
        _current_scene->shader_program->set_uniform("MVP", mvp);
        _current_scene->shader_program->set_uniform("MV3x3", mv33);
        _current_scene->shader_program->set_uniform("M", m);
        _current_scene->shader_program->set_uniform("V", v);
    }

}

IFrameBuffer *OGLRenderer::getRenderFramebuffer() { return _framebuffer.get(); }

}// namespace taixu