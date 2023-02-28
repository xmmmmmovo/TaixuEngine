//
// Created by xmmmmmovo on 2023/2/25.
//

#include "OGLVertexArray.hpp"

namespace taixu {

OGLVertexArray::OGLVertexArray() {}

void OGLVertexArray::bind() {
    glBindVertexArray(VAO);// Bind VAO
}

void OGLVertexArray::unbind() {
    glBindVertexArray(0);// Unbined VAO
}

void OGLVertexArray::setVBO(const IVertexBuffer& buffer) {}

void OGLVertexArray::setEBO(const IElementBuffer& ebo) {}

}// namespace taixu
