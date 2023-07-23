//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_VERTEX_BUFFER_HPP
#define TAIXUENGINE_VERTEX_BUFFER_HPP

#include "glad/glad.h"

#include "buffer_layout.hpp"
#include <common/base/noncopyable.hpp>

namespace taixu {

class IVertexBuffer : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void setData(std::size_t size, const void *data, GLenum usage,
                         GLint align, GLint size_of_type) = 0;

    [[nodiscard]] virtual GLint getAlign() const = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_VERTEX_BUFFER_HPP
