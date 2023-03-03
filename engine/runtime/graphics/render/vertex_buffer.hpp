//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_VERTEX_BUFFER_HPP
#define TAIXUENGINE_VERTEX_BUFFER_HPP

#include <any>

#include "buffer_layout.hpp"
#include "core/base/noncopyable.hpp"

namespace taixu {

class IVertexBuffer : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void setData(GLsizeiptr size, const void* data, GLenum usage) = 0;
    ~IVertexBuffer() override = default;
};

}// namespace taixu

#endif//TAIXUENGINE_VERTEX_BUFFER_HPP
