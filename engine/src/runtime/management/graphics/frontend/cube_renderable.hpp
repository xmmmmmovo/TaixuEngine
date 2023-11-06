//
// Created by xmmmmmovo on 2023/5/21.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP

#include <glad/glad.h>
#include <array>
#include <memory>

#include <runtime/management/graphics/render/shader.hpp>
#include <runtime/management/graphics/render/texture_cube.hpp>
#include <runtime/management/graphics/render/vertex_array.hpp>
#include <runtime/platform/opengl/ogl_element_buffer.hpp>
#include <runtime/platform/opengl/ogl_vertex_array.hpp>

namespace taixu {

class CubeRenderable : public PublicSingleton<CubeRenderable> {
    friend class PublicSingleton<CubeRenderable>;

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
    void init() noexcept {
        auto va = std::make_unique<OGLVertexArray>();
        va->bind();
        va->addVBO(OGLVertexBuffer{CUBE_VERTEX_COUNT / 3,
                                   &CUBE_VERTICES.front(), GL_STATIC_DRAW, 3},
                   GL_FLOAT);
        va->setEBO(OGLElementBuffer{CUBE_ELEMENT_COUNT, &CUBE_ELEMENTS.front(),
                                    GL_STATIC_DRAW});
        _sky_box_vertex_array = std::move(va);
        _sky_box_vertex_array->unbind();
    }

    void bind() const noexcept { _sky_box_vertex_array->bind(); }

    static void draw() noexcept {
        glDrawElements(GL_TRIANGLES, CUBE_ELEMENT_COUNT, GL_UNSIGNED_INT,
                       nullptr);
    }

    void unbind() const noexcept { _sky_box_vertex_array->unbind(); }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP
