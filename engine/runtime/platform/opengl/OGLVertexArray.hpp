//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLVERTEXARRAY_HPP
#define TAIXUENGINE_OGLVERTEXARRAY_HPP

#include <glad/glad.h>
#include<memory>
#include "graphics/render/vertex_array.hpp"
#include "graphics/render/element_buffer.hpp"
#include "graphics/render/vertex_buffer.hpp"
namespace taixu {

class OGLVertexArray : public IVertexArray {
private:
    BufferLayout                    layout{};
    std::uint32_t                   VAO{0};
    std::unique_ptr<IVertexBuffer>  VBO{};
    std::unique_ptr<IElementBuffer> EBO{};

public:
    OGLVertexArray();

    void bind() override;
    void unbind() override;
    void setVBO(const IVertexBuffer& buffer) override;
    void setEBO(const IElementBuffer& ebo) override;
    std::uint32_t getVAOid();
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXARRAY_HPP
