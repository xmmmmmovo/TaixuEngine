//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_GRAPHICS_RENDER_VERTEX_ARRAY_HPP
#define TAIXUENGINE_GRAPHICS_RENDER_VERTEX_ARRAY_HPP

#include <cstdint>
#include <vector>

#include "core/base/noncopyable.hpp"
#include "element_buffer.hpp"
#include "engine_args.hpp"
#include "management/graphics/render/render_api.hpp"
#include "vertex_buffer.hpp"

namespace taixu {

class IVertexArray : private noncopyable {
public:
    virtual void bind()   = 0;
    virtual void unbind() = 0;

    virtual void clear() = 0;

    virtual void draw(std::uint32_t cnt) = 0;
};

template<typename VboType = IVertexBuffer, typename EboType = IElementBuffer>
class AbstractVertexArray : public IVertexArray {
public:
    virtual void addVBO(VboType &&vbo,GLenum type) = 0;
    virtual void setEBO(EboType &&ebo) = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_GRAPHICS_RENDER_VERTEX_ARRAY_HPP
