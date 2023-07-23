//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP

#include <common/base/path.hpp>
#include <runtime/management/graphics/frontend/cube_renderable.hpp>
#include <runtime/management/graphics/render/shader.hpp>
#include <runtime/management/graphics/render/texture_cube.hpp>
#include <runtime/management/graphics/render/vertex_array.hpp>
#include <runtime/platform/opengl/ogl_element_buffer.hpp>
#include <runtime/platform/opengl/ogl_vertex_array.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>

namespace taixu {

inline void drawSkybox(IShaderProgram *shader, ITextureCube *cubetexture,
                       CubeRenderable *cube) {
    glCullFace(GL_FRONT);
    glDepthFunc(
            GL_LEQUAL);// change depth function so depth test passes when values are equal to depth buffer's content
    shader->use();
    cube->bind();
    cubetexture->bind();
    cube->draw();
    cube->unbind();
    glDepthFunc(GL_LESS);// set depth function back to default
    glCullFace(GL_BACK);
}

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
