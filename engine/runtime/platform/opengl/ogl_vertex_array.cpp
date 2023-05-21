//
// Created by xmmmmmovo on 2023/2/25.
//

#include "ogl_vertex_array.hpp"

namespace taixu {

OGLVertexArray::OGLVertexArray() { glGenVertexArrays(1, &VAO); }

OGLVertexArray::~OGLVertexArray() { glDeleteBuffers(1, &VAO); }

void OGLVertexArray::bind() {
    glBindVertexArray(VAO);// Bind VAO
}

void OGLVertexArray::unbind() {
    glBindVertexArray(0);// Unbined VAO
}

void OGLVertexArray::addVBO(OGLVertexBuffer &&vbo,GLenum type) {
    std::size_t const idx = VBO.size();
    glEnableVertexAttribArray(idx);
    vbo.bind();
    if(type == GL_INT)
        glVertexAttribIPointer(idx, vbo.getAlign(), GL_INT, 0, nullptr);
    else
        glVertexAttribPointer(idx, vbo.getAlign(), GL_FLOAT, GL_FALSE, 0, nullptr);
    this->VBO.push_back(std::move(vbo));
}

void OGLVertexArray::setEBO(OGLElementBuffer &&ebo) {
    ebo.bind();
    this->EBO = std::move(ebo);
}

}// namespace taixu
