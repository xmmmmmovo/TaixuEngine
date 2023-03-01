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
    explicit OGLElementBuffer(std::vector<std::uint32_t> const& indices,
                              GLenum usage = GL_STATIC_DRAW);

    void bind() override;
    void unbind() override;

    //~OGLElementBuffer() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLELEMENTBUFFER_HPP
