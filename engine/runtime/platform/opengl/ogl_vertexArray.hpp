//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_VERTEXARRAY_HPP
#define TAIXUENGINE_OGL_VERTEXARRAY_HPP

#include <glad/glad.h>

#include <memory>

#include "graphics/render/vertex_array.hpp"
#include "ogl_elementBuffer.hpp"
#include "ogl_vertexBuffer.hpp"

namespace taixu {

class OGLVertexArray : public IVertexArray<OGLVertexBuffer, OGLElementBuffer> {
private:
    std::uint32_t                VAO{0};
    /**
     * 这里就让他copy 用空间换时间
     * @brief VBO
     */
    std::vector<OGLVertexBuffer> VBO{};
    OGLElementBuffer             EBO{};

public:
    OGLVertexArray();
    ~OGLVertexArray() override;
    void bind() override;
    void unbind() override;
    void addVBO(OGLVertexBuffer &&vbo) override;
    void setEBO(OGLElementBuffer &&ebo) override;
    void clear()
    {
        GLuint vboID=VBO[0].getAlign();
        glDeleteBuffers(1, &vboID);
        VBO.clear();
        GLuint eboID=EBO.getbufferID();
        glDeleteBuffers(1, &eboID);
    };
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_VERTEXARRAY_HPP
