//
// Created by xmmmmmovo on 2023/2/25.
//

#include "ogl_element_buffer.hpp"

#include "spdlog/spdlog.h"

namespace taixu {

OGLElementBuffer::OGLElementBuffer() { glGenBuffers(1, &EBO); }

OGLElementBuffer::OGLElementBuffer(const std::vector<std::uint32_t> &indices,
                                   GLenum                            usage)
    : OGLElementBuffer() {
    this->bind();
    this->setData(indices, usage);
    this->unbind();
}

void OGLElementBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }

void OGLElementBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void OGLElementBuffer::setData(const std::vector<std::uint32_t> &indices,
                               GLenum                            usage) {
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint32_t)),
            &indices[0], usage);
}

OGLElementBuffer::~OGLElementBuffer() { glDeleteBuffers(1, &EBO); }

}// namespace taixu
