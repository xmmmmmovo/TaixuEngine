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

void OGLVertexArray::addVBO(OGLVertexBuffer const& vbo) {
//    this->VBO.emplace_back(std::move(vbo));
}

void OGLVertexArray::setEBO(OGLElementBuffer const&& ebo) {
//    this->EBO = ebo;
}

}// namespace taixu
