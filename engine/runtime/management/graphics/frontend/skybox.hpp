//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP

#include "management/graphics/render/shader.hpp"
#include "management/graphics/render/texture_cube.hpp"
#include "management/graphics/render/vertex_array.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>

namespace taixu {

static float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

class Skybox {
private:
    std::unique_ptr<IShaderProgram> _sky_box_shader{nullptr};
    std::unique_ptr<ITextureCube>   _sky_box_texture{nullptr};
    std::unique_ptr<IVertexArray>   _sky_box_vertex_array{nullptr};

    unsigned int skyboxVAO, skyboxVBO;

    static constexpr std::size_t CUBE_VERTEX_COUNT  = 24;
    static constexpr std::size_t CUBE_ELEMENT_COUNT = 36;

    std::array<GLfloat, CUBE_VERTEX_COUNT> cube_vertices = {
            // front
            -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0,
            // back
            -1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0};

    std::array<std::uint32_t, CUBE_ELEMENT_COUNT> cube_elements = {
            // front
            0, 1, 2, 2, 3, 0,
            // right
            1, 5, 6, 6, 2, 1,
            // back
            7, 6, 5, 5, 4, 7,
            // left
            4, 0, 3, 3, 7, 4,
            // bottom
            4, 5, 1, 1, 0, 4,
            // top
            3, 2, 6, 6, 7, 3};

public:
    explicit Skybox(std::unique_ptr<ITextureCube>   cube,
                    std::unique_ptr<IShaderProgram> shader)
        : _sky_box_texture(std::move(cube)),
          _sky_box_shader(std::move(shader)) {
        auto va = std::make_unique<OGLVertexArray>();
        va->addVBO(OGLVertexBuffer{CUBE_VERTEX_COUNT / 3,
                                   &cube_vertices.front(), GL_STATIC_DRAW, 3});
        va->setEBO(OGLElementBuffer{CUBE_ELEMENT_COUNT, &cube_elements.front(),
                                    GL_STATIC_DRAW});
        _sky_box_vertex_array = std::move(va);

        _sky_box_shader->use();
        _sky_box_shader->set_uniform("skybox", 0);
    }

    void bind_uniform_block(const std::string_view &name,
                            std::uint32_t           idx) const noexcept {
        _sky_box_shader->bind_uniform_block(name, idx);
    }

    void draw() const {
        glDepthMask(GL_FALSE);
        _sky_box_shader->use();
        _sky_box_vertex_array->bind();
        _sky_box_texture->bind();
        glDrawElements(GL_TRIANGLES, CUBE_ELEMENT_COUNT, GL_UNSIGNED_INT,
                       nullptr);
        glDepthMask(GL_TRUE);
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_SKYBOX_HPP
