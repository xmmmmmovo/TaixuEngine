//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP

#include "core/base/path.hpp"
#include "management/graphics/render/shader.hpp"
#include "management/graphics/render/texture_cube.hpp"
#include "management/graphics/render/vertex_array.hpp"
#include "platform/opengl/ogl_element_buffer.hpp"
#include "platform/opengl/ogl_vertex_array.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>

namespace taixu {

class Skybox {
private:
    std::unique_ptr<IVertexArray> _sky_box_vertex_array{nullptr};

    static constexpr std::size_t CUBE_VERTEX_COUNT  = 24;
    static constexpr std::size_t CUBE_ELEMENT_COUNT = 36;

    static constexpr std::array<GLfloat, CUBE_VERTEX_COUNT> CUBE_VERTICES = {
            //   Coordinates
            -1.0f, -1.0f, 1.0f, //        7--------6
            1.0f,  -1.0f, 1.0f, //       /|       /|
            1.0f,  -1.0f, -1.0f,//      4--------5 |
            -1.0f, -1.0f, -1.0f,//      | |      | |
            -1.0f, 1.0f,  1.0f, //      | 3------|-2
            1.0f,  1.0f,  1.0f, //      |/       |/
            1.0f,  1.0f,  -1.0f,//      0--------1
            -1.0f, 1.0f,  -1.0f};

    static constexpr std::array<std::uint32_t, CUBE_ELEMENT_COUNT>
            CUBE_ELEMENTS = {// Right
                    1, 2, 6, 6, 5, 1,
                    // Left
                    0, 4, 7, 7, 3, 0,
                    // Top
                    4, 5, 6, 6, 7, 4,
                    // Bottom
                    0, 3, 2, 2, 1, 0,
                    // Back
                    0, 1, 5, 5, 4, 0,
                    // Front
                    3, 7, 6, 6, 2, 3};

public:
    explicit Skybox() {
        auto va = std::make_unique<OGLVertexArray>();
        va->bind();
        va->addVBO(OGLVertexBuffer{CUBE_VERTEX_COUNT / 3,
                                   &CUBE_VERTICES.front(), GL_STATIC_DRAW, 3},GL_FLOAT);
        va->setEBO(OGLElementBuffer{CUBE_ELEMENT_COUNT, &CUBE_ELEMENTS.front(),
                                    GL_STATIC_DRAW});
        _sky_box_vertex_array = std::move(va);
    }

    void draw(IShaderProgram *shader, ITextureCube *cubetexture) const {
        glDepthFunc(
                GL_LEQUAL);// change depth function so depth test passes when values are equal to depth buffer's content
        shader->use();
        _sky_box_vertex_array->bind();
        cubetexture->bind();
        _sky_box_vertex_array->draw(CUBE_ELEMENT_COUNT);
        glDepthFunc(GL_LESS);// set depth function back to default
    }
};
}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
