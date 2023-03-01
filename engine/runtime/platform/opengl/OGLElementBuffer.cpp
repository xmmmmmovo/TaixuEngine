//
// Created by xmmmmmovo on 2023/2/25.
//

#include "OGLElementBuffer.hpp"

namespace taixu {
OGLElementBuffer::OGLElementBuffer(std::vector<std::uint32_t> const& indices,
                                   GLenum usage) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint32_t)),
            &indices[0], usage);
}

void OGLElementBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }

void OGLElementBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

//OGLElementBuffer::~OGLElementBuffer() { glDeleteBuffers(1, &EBO); }
}// namespace taixu
