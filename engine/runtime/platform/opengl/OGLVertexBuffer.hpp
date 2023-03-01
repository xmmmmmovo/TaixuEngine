//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLVERTEXBUFFER_HPP
#define TAIXUENGINE_OGLVERTEXBUFFER_HPP

#include <glm/glm.hpp>
#include "graphics/render/vertex_buffer.hpp"

namespace taixu {

class OGLVertexBuffer : public IVertexBuffer {
private:
    unsigned int VBO{0};

public:
    OGLVertexBuffer();

    void bind() override;
    void unbind() override;

    void setData(GLsizeiptr size, const void* data,
                 GLenum usage = GL_STATIC_DRAW) override;
    //~OGLVertexBuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXBUFFER_HPP
