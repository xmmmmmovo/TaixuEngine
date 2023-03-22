//
// Created by xmmmmmovo on 2023/2/25.
//

#include <glad/glad.h>

#include "OGLVertexBuffer.hpp"

namespace taixu {
OGLVertexBuffer::OGLVertexBuffer() = default;

void OGLVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind VBO
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

OGLVertexBuffer::~OGLVertexBuffer() { glDeleteBuffers(1, &VBO); }
}// namespace taixu