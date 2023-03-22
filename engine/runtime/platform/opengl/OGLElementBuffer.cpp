//
// Created by xmmmmmovo on 2023/2/25.
//

#include "OGLElementBuffer.hpp"

namespace taixu {

OGLElementBuffer::OGLElementBuffer() { glGenBuffers(1, &EBO); }

void OGLElementBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }

void OGLElementBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void OGLElementBuffer::setData(GLsizeiptr                        size,
                               const std::vector<std::uint32_t>& indices,
                               std::uint32_t attribute, GLenum usage) {
    bind();
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(indices.size() * sizeof(std::uint32_t)),
            &indices[0], usage);
}

OGLElementBuffer::~OGLElementBuffer() { glDeleteBuffers(1, &EBO); }

}// namespace taixu
