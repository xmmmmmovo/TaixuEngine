//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLVERTEXARRAY_HPP
#define TAIXUENGINE_OGLVERTEXARRAY_HPP

#include <glad/glad.h>

#include "graphics/render/vertex_array.hpp"

namespace taixu {

class OGLVertexArray : public IVertexArray {
private:
    BufferLayout layout{};

public:
    OGLVertexArray();

    void bind() override;
    void unbind() override;
    void setVBO(const IVertexBuffer& buffer) override;
    void setEBO(const IElementBuffer& ebo) override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXARRAY_HPP
