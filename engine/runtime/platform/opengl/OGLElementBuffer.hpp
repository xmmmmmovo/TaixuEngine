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
    OGLElementBuffer(const std::vector<std::uint32_t>& indices, GLenum usage);

    void bind() override;
    void unbind() override;
    std::uint32_t getbufferID(){return EBO;};
    void setData(const std::vector<std::uint32_t>& indices,
                 GLenum                            usage) override;
    void setDataInner(const std::vector<std::uint32_t>& indices, GLenum usage);

    ~OGLElementBuffer() override;

    OGLElementBuffer(OGLElementBuffer&& other) noexcept            = default;
    OGLElementBuffer& operator=(OGLElementBuffer&& other) noexcept = default;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLELEMENTBUFFER_HPP
