//
// Created by xmmmmmovo on 2023/4/6.
//

#include "ogl_renderer.hpp"
#include "management/ecs/components/rigid_body/rigid_body_component.hpp"
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

    _render_shader = std::make_unique<OGLShaderProgram>(VERT_VERT, FRAG_FRAG);
    _render_shader->use();
    _render_shader->bind_uniform_block("Matrices", 0);
    _render_shader->bind_uniform_block("LightSourse", 1);
    _render_shader->bind_uniform_block("Material", 2);

    _skybox_shader =
            std::make_unique<OGLShaderProgram>(SKYBOX_VERT, SKYBOX_FRAG);
    _skybox_shader->use();
    _skybox_shader->bind_uniform_block("Matrices", 0);
    _skybox_shader->set_uniform("skybox", 0);
}

void OGLRenderer::update(float delta_time) {
    _framebuffer->bind();
    clear(CLEAR_COLOR);

    if (_current_scene != nullptr) {
        updateCamera(delta_time);

        _matrices.projection = _current_scene->_camera->getProjectionMatrix();
        auto view            = _current_scene->_camera->getViewMatrix();

        _matrices.view = glm::mat4(glm::mat3(view));
        _matrices.vp   = _matrices.projection * _matrices.view;

        _matrices_ubo.bind();
        _matrices_ubo.updateData(_matrices, 0);
        _matrices_ubo.unbind();

        _current_scene->_skybox.draw(_skybox_shader.get(),
                                     _current_scene->_skybox_texture.get());

        _matrices.view = view;
        _matrices.vp   = _matrices.projection * _matrices.view;
        _matrices_ubo.bind();
        _matrices_ubo.updateData(_matrices, 0);
        _matrices_ubo.unbind();

        for (auto const &entity : _renderable_system->entities()) {
            if (_current_scene->_ecs_coordinator.anyOf<LightComponent>(
                        entity)) {
                auto light = _current_scene->_ecs_coordinator
                                     .getComponent<LightComponent>(entity);

                auto light_trans =
                        _current_scene->_ecs_coordinator
                                .getComponent<TransformComponent>(entity);
                LightsInfo lightInfo;
                lightInfo.light_position =
                        glm::vec4(light_trans.translate(), 1.0f);
                lightInfo.light_color = light.light_color;
                lightInfo.camera_position =
                        glm::vec4(_current_scene->_camera->Position, 1.0f);
                _lights_ubo.bind();
                _lights_ubo.setData(lightInfo, 1);
                _lights_ubo.unbind();
                break;
            }
        }

        // ///////////////////////////////////////////////////////////////////////
        MaterialInfo m;
        m.shininess = 32;
        m.ambient   = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
        m.diffuse   = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f);
        m.specular  = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        m.emissive  = glm::vec4(0.f, 0.f, 0.f, 1.0f);

        _material_ubo.bind();
        _material_ubo.setData(m, 2);
        _material_ubo.unbind();
        ///////////////////////////////////////////////////////////////////////

        _render_shader->use();
        for (auto const &entity : _renderable_system->entities()) {
            if (_current_scene->_ecs_coordinator.anyOf<RenderableComponent>(
                        entity)) {
                auto const &renderable =
                        _current_scene->_ecs_coordinator
                                .getComponent<RenderableComponent>(entity);
                if (renderable.visiable) {
                    auto &trans =
                            _current_scene->_ecs_coordinator
                                    .getComponent<TransformComponent>(entity);
                    trans.makeTransformMatrix();
                    _render_shader->set_uniform("model", trans.transform());
                    _render_shader->set_uniform("textureSampler", 0);
                    ////////////////////////////////////////////////////
                    if (entity < _current_scene->_textures2D.size())
                        _current_scene->_textures2D[entity].get()->bind(0);
                    ////////////////////////////////////////////////////
                    for (auto &mesh :
                         renderable.model->gpu_data.value().meshes) {
                        mesh.vao->draw(mesh.index_count);
                    }
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