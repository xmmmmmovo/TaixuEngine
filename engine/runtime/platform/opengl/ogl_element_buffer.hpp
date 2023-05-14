//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_ELEMENTBUFFER_HPP
#define TAIXUENGINE_OGL_ELEMENTBUFFER_HPP

#include <glad/glad.h>

#include "management/graphics/render/element_buffer.hpp"
#include <cstdint>

namespace taixu {

class OGLElementBuffer final : public IElementBuffer {
private:
    unsigned int EBO{0};

public:
    OGLElementBuffer();

    OGLElementBuffer(const std::vector<std::uint32_t> &indices, GLenum usage);

    void                        bind() override;
    void                        unbind() override;
    [[nodiscard]] std::uint32_t getbufferID() const { return EBO; };
    void setData(const std::vector<std::uint32_t> &indices,
                 GLenum                            usage) override;

    ~OGLElementBuffer() override;

    OGLElementBuffer(OGLElementBuffer &&other) noexcept : EBO(other.EBO) {
        other.EBO = 0;
    }

    OGLElementBuffer &operator=(OGLElementBuffer &&other) noexcept {
        if (this != &other) {
            EBO       = other.EBO;
            other.EBO = 0;
        }
        return *this;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_ELEMENTBUFFER_HPP
