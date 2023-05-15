//
// Created by xmmmmmovo on 2023/2/25.
//

#include "ogl_element_buffer.hpp"

#include "spdlog/spdlog.h"

namespace taixu {

OGLElementBuffer::OGLElementBuffer() { glGenBuffers(1, &EBO); }

OGLElementBuffer::OGLElementBuffer(std::size_t          size,
                                   const std::uint32_t *indices, GLenum usage)
    : OGLElementBuffer() {
    this->bind();
    this->setData(size, indices, usage);
    this->unbind();
}

void OGLElementBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }

void OGLElementBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void OGLElementBuffer::setData(std::size_t size, const std::uint32_t *indices,
                               GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(size * sizeof(std::uint32_t)), indices,
                 usage);
}

OGLElementBuffer::~OGLElementBuffer() { glDeleteBuffers(1, &EBO); }

}// namespace taixu
