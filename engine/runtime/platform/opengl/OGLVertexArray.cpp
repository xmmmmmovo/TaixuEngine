//
// Created by xmmmmmovo on 2023/2/25.
//

#include "OGLVertexArray.hpp"

namespace taixu {

OGLVertexArray::OGLVertexArray() { glGenVertexArrays(1, &VAO); }

OGLVertexArray::~OGLVertexArray() { glDeleteBuffers(1, &VAO); }

void OGLVertexArray::bind() {
    glBindVertexArray(VAO);// Bind VAO
}

void OGLVertexArray::unbind() {
    glBindVertexArray(0);// Unbined VAO
}

void OGLVertexArray::setVBO() {}

void OGLVertexArray::setEBO() {}

std::uint32_t OGLVertexArray::getVAOid() {return VAO;}



}// namespace taixu
