//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_ELEMENTBUFFER_HPP
#define TAIXUENGINE_OGL_ELEMENTBUFFER_HPP

#include <glad/glad.h>

#include "graphics/render/element_buffer.hpp"

namespace taixu {

class OGLElementBuffer : public IElementBuffer {
private:
    unsigned int EBO{0};

public:
    OGLElementBuffer();
    OGLElementBuffer(const std::vector<std::uint32_t>& indices, GLenum usage);

    void bind() override;
    void unbind() override;
    unsigned int getbufferID(){return EBO;};
    void setData(const std::vector<std::uint32_t>& indices,
                 GLenum                            usage) override;
    void setDataInner(const std::vector<std::uint32_t>& indices, GLenum usage);

    ~OGLElementBuffer() override;

    OGLElementBuffer(OGLElementBuffer&& other) noexcept : EBO(other.EBO) {
        other.EBO = 0;
    }

    OGLElementBuffer& operator=(OGLElementBuffer&& other) noexcept {
        if (this != &other) {
            EBO       = other.EBO;
            other.EBO = 0;
        }
        return *this;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_ELEMENTBUFFER_HPP