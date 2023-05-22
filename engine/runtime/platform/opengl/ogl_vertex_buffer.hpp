//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_VERTEXBUFFER_HPP
#define TAIXUENGINE_OGL_VERTEXBUFFER_HPP

#include <glm/glm.hpp>

#include "management/graphics/render/vertex_buffer.hpp"

namespace taixu {

class OGLVertexBuffer final : public IVertexBuffer {
private:
    unsigned int VBO{};
    GLint        align{0};

public:
    OGLVertexBuffer();
    OGLVertexBuffer(std::size_t size, const void *data, GLenum usage,
                    GLint align);

    void                        bind() override;
    void                        unbind() override;
    [[nodiscard]] std::uint32_t getbufferID() const { return VBO; }

    void setData(std::size_t size, const void *data, GLenum usage, GLint align,
                 GLint size_of_type = sizeof(float)) override;

    [[nodiscard]] GLint getAlign() const override;

    ~OGLVertexBuffer() override;

    OGLVertexBuffer(OGLVertexBuffer &&other) noexcept
        : VBO(other.VBO), align(other.align) {
        other.VBO   = 0;
        other.align = 0;
    }

    OGLVertexBuffer &operator=(OGLVertexBuffer &&other) noexcept {
        if (this == &other) { return *this; }

        VBO         = other.VBO;
        align       = other.align;
        other.VBO   = 0;
        other.align = 0;
        return *this;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_VERTEXBUFFER_HPP
