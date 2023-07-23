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

constexpr std::array<float, 3> CLEAR_COLOR{0.5294117647f, 0.8078431373f,
                                           0.9215686275f};

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

    _render_shader = std::make_unique<OGLShaderProgram>(VERT_VERT, FRAG_FRAG);
    _render_shader->use();

    _render_shader->bind_uniform_block("Matrices", 0);
    _render_shader->bind_uniform_block("Material", 1);
    _render_shader->bind_uniform_block("LightSource", 2);
    _render_shader->set_uniform("diffuseTexture", 0);

    _skybox_shader =
            std::make_unique<OGLShaderProgram>(SKYBOX_VERT, SKYBOX_FRAG);
    _animation_shader =
            std::make_unique<OGLShaderProgram>(SKELETON_VERT, SKELETON_FRAG);

    _skybox_shader->use();
    _skybox_shader->bind_uniform_block("Matrices", 0);
    _skybox_shader->set_uniform("skybox", 0);

    _animation_shader->use();
    _animation_shader->bind_uniform_block("Matrices", 0);

    _cube_renderable = &CubeRenderable::getInstance();
    _cube_renderable->init();
}

void OGLRenderer::update(float delta_time) {
    _framebuffer->bind();
    clear(CLEAR_COLOR);

    if (_current_scene != nullptr) {
        updateCamera(delta_time);

        _matrices.projection = _current_scene->_camera->getProjectionMatrix();
        auto view            = _current_scene->_camera->getViewMatrix();
        _matrices.camera_pos =
                glm::vec4(_current_scene->_camera->Position, 1.0f);

        _matrices.view = glm::mat4(glm::mat3(view));
        _matrices.vp   = _matrices.projection * _matrices.view;

        _matrices_ubo.bind();
        _matrices_ubo.updateData(_matrices);
        _matrices_ubo.unbind();

        drawSkybox(_skybox_shader.get(), _current_scene->_skybox_texture.get(),
                   _cube_renderable);

        _matrices.view = view;
        _matrices.vp   = _matrices.projection * _matrices.view;
        _matrices_ubo.bind();
        _matrices_ubo.updateData(_matrices);
        _matrices_ubo.unbind();

        // 处理光照
        _lights = {};

        for (auto const& entity : _light_system->entities()) {
            if (_current_scene->_ecs_coordinator
                        .allOf<LightComponent, TransformComponent>(entity)) {
                auto& light_comp =
                        _current_scene->_ecs_coordinator
                                .getComponent<LightComponent>(entity);
                auto& trans_comp =
                        _current_scene->_ecs_coordinator
                                .getComponent<TransformComponent>(entity);
                //                spdlog::debug("translate: {} {} {}",
                //                trans_comp.translate().x,
                //                              trans_comp.translate().y,
                //                              trans_comp.translate().z);
                _lights.pointLights[_lights.pointLightCount] = {
                        .position  = glm::vec4(trans_comp.translate(), 1.0f),
                        .constant  = 1.0f,
                        .linear    = 0.09f,
                        .quadratic = 0.032f,
                        .ambient   = light_comp.light_color,
                        .diffuse   = light_comp.light_color,
                        .specular  = light_comp.light_color,
                };
                ++_lights.pointLightCount;
            }
        }

        _lights_ubo.bind();
        _lights_ubo.updateData(_lights);
        _lights_ubo.unbind();


        _render_shader->use();
        for (auto const& entity : _renderable_system->entities()) {
            if (_current_scene->_ecs_coordinator.anyOf<RenderableComponent>(
                        entity)) {
                auto const& renderable =
                        _current_scene->_ecs_coordinator
                                .getComponent<RenderableComponent>(entity);
                if (renderable.visiable) {
                    auto& trans =
                            _current_scene->_ecs_coordinator
                                    .getComponent<TransformComponent>(entity);
                    trans.makeTransformMatrix();


                    _render_shader->set_uniform("model", trans.transform());
                    _render_shader->set_uniform(
                            "invModel3x3",
                            glm::mat3(glm::transpose(
                                    glm::inverse(trans.transform()))));
                    for (auto& mesh :
                         renderable.model->gpu_data.value().meshes) {
                        if (mesh.mat_index.has_value()) {
                            auto const& material =
                                    renderable.model
                                            ->materials[mesh.mat_index.value()];
                            _material.ambient =
                                    glm::vec4(material.ambient, 1.0f);
                            _material.diffuse =
                                    glm::vec4(material.diffuse, 1.0f);
                            _material.specular =
                                    glm::vec4(material.specular, 1.0f);
                            _material.emissive =
                                    glm::vec4(material.emissive, 1.0f);
                            _material.shininess = material.shininess;

                            if (material.diffuse_tex != nullptr) {
                                material.diffuse_tex->texture->bind(0);
                            } else {
                                _default_texture->bind(0);
                            }

                        } else {
                            _material.ambient   = glm::vec4(1.0f);
                            _material.diffuse   = glm::vec4(1.0f);
                            _material.specular  = glm::vec4(1.0f);
                            _material.emissive  = glm::vec4(0.0f);
                            _material.shininess = 32.0f;

                            _default_texture->bind(0);
                        }
                        _material_ubo.bind();
                        _material_ubo.updateData(_material);
                        _material_ubo.unbind();
                        mesh.vao->draw(mesh.index_count);
                    }
                }
            } else if (_current_scene->_ecs_coordinator
                               .anyOf<SkeletonComponent>(entity)) {
                _animation_shader->use();
                auto const& skeleton =
                        _current_scene->_ecs_coordinator
                                .getComponent<SkeletonComponent>(entity);

                auto& trans = _current_scene->_ecs_coordinator
                                      .getComponent<TransformComponent>(entity);
                trans.makeTransformMatrix();

                _animation_shader->set_uniform("model", trans.transform());

                auto transforms = skeleton.m_FinalBoneMatrices;
                for (int i = 0; i < transforms.size(); ++i)
                    _animation_shader->setMat4Array(
                            "finalBonesMatrices[" + std::to_string(i) + "]",
                            transforms[i]);

                for (auto& mesh :
                     skeleton.fbx->model->gpu_data.value().meshes) {
                    mesh.vao->draw(mesh.index_count);
                }
            }
        }
    }

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