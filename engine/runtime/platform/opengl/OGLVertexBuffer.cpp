//
// Created by xmmmmmovo on 2023/2/25.
//

#include <glad/glad.h>

#include "OGLVertexBuffer.hpp"

namespace taixu {
OGLVertexBuffer::OGLVertexBuffer() = default;

void OGLVertexBuffer::bind() {
    for (auto& vbo : VBO) glBindBuffer(GL_ARRAY_BUFFER, vbo);// Bind VBO
}

void OGLVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbined VBO
}

void OGLVertexBuffer::setData(GLsizeiptr size, const void* data,
                              std::uint32_t attribute, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}

OGLVertexBuffer::~OGLVertexBuffer() {
    glDeleteBuffers(static_cast<int>(VBO.size()), &VBO[0]);
}
}// namespace taixu