//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_VERTEX_ARRAY_HPP
#define TAIXUENGINE_VERTEX_ARRAY_HPP

#include <vector>

#include "core/base/noncopyable.hpp"
#include "element_buffer.hpp"
#include "vertex_buffer.hpp"

namespace taixu {

class IVertexArray : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void setVBO(IVertexBuffer const &buffer) = 0;
    virtual void setEBO(IElementBuffer const &ebo)   = 0;

    ~IVertexArray() override = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_VERTEX_ARRAY_HPP
