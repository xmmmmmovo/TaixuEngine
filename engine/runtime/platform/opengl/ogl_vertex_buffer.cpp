//
// Created by xmmmmmovo on 2023/2/25.
//

#include <glad/glad.h>

#include "ogl_vertex_buffer.hpp"

namespace taixu {
OGLVertexBuffer::OGLVertexBuffer() {
    glGenBuffers(1, &VBO);// Generate VBO
};

OGLVertexBuffer::OGLVertexBuffer(std::size_t size, const void *data,
                                 GLenum usage, GLint align)
    : OGLVertexBuffer() {
    bind();
    setData(size, data, usage, align);
    unbind();
}

void OGLVertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind VBO
}

void OGLVertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);// Unbined VBO
}

void OGLVertexBuffer::setData(std::size_t size, const void *data, GLenum usage,
                              GLint align) {
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(size) * align * sizeof(float), data,
                 usage);
    this->align = align;
}

GLint OGLVertexBuffer::getStride() const { return this->stride; }

GLint OGLVertexBuffer::getAlign() const { return this->align; }

OGLVertexBuffer::~OGLVertexBuffer() {
    glDeleteBuffers(1, &VBO);
}

}// namespace taixu