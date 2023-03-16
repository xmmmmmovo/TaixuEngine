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

class OGLVertexArray : public IVertexArray {
private:
    std::uint32_t                   VAO{0};
    std::unique_ptr<IVertexBuffer>  VBO{};
    std::unique_ptr<IElementBuffer> EBO{};

public:
    OGLVertexArray();
    ~OGLVertexArray() override;
    void bind() override;
    void unbind() override;
    void setVBO(std::unique_ptr<IVertexBuffer>& vbo) override;
    void setEBO(std::unique_ptr<IElementBuffer>& ebo) override;
    [[nodiscard]] std::uint32_t getVAOid() const;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXARRAY_HPP
