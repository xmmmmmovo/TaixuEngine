//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_UNIFORM_BUFFER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_UNIFORM_BUFFER_HPP

#include <common/base/noncopyable.hpp>

namespace taixu {

class IUniformBuffer : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_UNIFORM_BUFFER_HPP
