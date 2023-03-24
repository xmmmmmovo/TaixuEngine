//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLVERTEXARRAY_HPP
#define TAIXUENGINE_OGLVERTEXARRAY_HPP

#include <glad/glad.h>

#include <memory>

#include "OGLElementBuffer.hpp"
#include "OGLVertexBuffer.hpp"
#include "graphics/render/vertex_array.hpp"

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
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXARRAY_HPP
