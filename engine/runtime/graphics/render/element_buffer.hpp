//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_ELEMENT_BUFFER_HPP
#define TAIXUENGINE_ELEMENT_BUFFER_HPP

#include <glad/glad.h>

#include <vector>

#include "core/base/noncopyable.hpp"

namespace taixu {

class IElementBuffer : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void setData(const std::vector<std::uint32_t>& indices,
                         GLenum                            usage) = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_ELEMENT_BUFFER_HPP
