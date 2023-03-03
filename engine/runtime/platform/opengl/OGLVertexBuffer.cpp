//
// Created by xmmmmmovo on 2023/2/25.
//

#include <glad/glad.h>

#include "OGLVertexBuffer.hpp"

namespace taixu {
OGLVertexBuffer::OGLVertexBuffer() {
    glGenBuffers(1, &VBO);// Generate 1 buffer
}

void OGLVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind VBO
}

void OGLVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbined VBO
}

void OGLVertexBuffer::setData(GLsizeiptr size,
                              const void* data,
                              GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

OGLVertexBuffer::~OGLVertexBuffer() { glDeleteBuffers(1, &VBO); }
}// namespace taixu