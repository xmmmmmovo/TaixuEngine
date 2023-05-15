//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_TEXTURE_CUBE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_TEXTURE_CUBE_HPP

#include <cstdint>

#include "core/base/noncopyable.hpp"

namespace taixu {

class ITextureCube : private noncopyable {
public:
    virtual std::uint32_t getTextureID() const = 0;

    virtual void bind(std::uint32_t slot = 0) const = 0;

    virtual bool operator==(const ITextureCube &other) const = 0;
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_TEXTURE_CUBE_HPP
