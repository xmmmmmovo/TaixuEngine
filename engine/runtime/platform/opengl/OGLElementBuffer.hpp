//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLELEMENTBUFFER_HPP
#define TAIXUENGINE_OGLELEMENTBUFFER_HPP

#include <glad/glad.h>

#include "graphics/render/element_buffer.hpp"

namespace taixu {

class OGLElementBuffer : public IElementBuffer {
private:
    std::uint32_t EBO{0};

public:
    OGLElementBuffer();

    void bind() override;
    void unbind() override;

    void setData(GLsizeiptr size, std::vector<std::uint32_t> const& indices,
                 std::uint32_t attribute, GLenum usage) override;

    ~OGLElementBuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLELEMENTBUFFER_HPP
