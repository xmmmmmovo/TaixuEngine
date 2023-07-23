//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_VERTEXARRAY_HPP
#define TAIXUENGINE_OGL_VERTEXARRAY_HPP

#include <glad/glad.h>

#include <cstdint>
#include <memory>

#include <runtime/management/graphics/render/vertex_array.hpp>
#include "ogl_element_buffer.hpp"
#include "ogl_vertex_buffer.hpp"

namespace taixu {

class OGLVertexArray
    : public AbstractVertexArray<OGLVertexBuffer, OGLElementBuffer> {
private:
    std::uint32_t                VAO{0};
    /**
     * 这里就让他copy 用空间换时间
     * @brief VBO
     */
    std::vector<OGLVertexBuffer> VBO{};
    OGLElementBuffer             EBO{};

public:
    OGLVertexArray();
    ~OGLVertexArray() override;

    void bind() override;
    void unbind() override;
    void addVBO(OGLVertexBuffer &&vbo, GLenum type) override;
    void setEBO(OGLElementBuffer &&ebo) override;

    void clear() override {
        VBO.clear();
        GLuint const ebo_id = EBO.getbufferID();
        glDeleteBuffers(1, &ebo_id);
    };

    void draw(std::uint32_t cnt) override {
        bind();
        glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(cnt),
                       GL_UNSIGNED_INT, nullptr);
        unbind();
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_VERTEXARRAY_HPP
