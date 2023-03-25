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

void OGLVertexArray::addVBO(OGLVertexBuffer &&vbo) {
    std::size_t const idx = VBO.size();
    vbo.bind();
    glVertexAttribPointer(idx, vbo.getAlign(), GL_FLOAT, GL_FALSE, 0, nullptr);
    this->VBO.emplace_back(std::move(vbo));
    glEnableVertexAttribArray(idx);
}

void OGLVertexArray::setEBO(OGLElementBuffer &&ebo) {
    ebo.bind();
    this->EBO = std::move(ebo);
}

}// namespace taixu
