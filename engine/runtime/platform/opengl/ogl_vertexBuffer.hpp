//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGL_VERTEXBUFFER_HPP
#define TAIXUENGINE_OGL_VERTEXBUFFER_HPP

#include <glm/glm.hpp>

#include "graphics/render/vertex_buffer.hpp"

namespace taixu {

class OGLVertexBuffer : public IVertexBuffer {
private:
    unsigned int VBO{};
    GLint        stride{0};
    GLint        align{0};

public:
    OGLVertexBuffer();
    OGLVertexBuffer(std::size_t size, const void *data, GLenum usage,
                    GLint align);

    void bind() override;
    void unbind() override;
    std::uint32_t getbufferID(){return VBO;};
    void setData(std::size_t size, const void *data, GLenum usage,
                 GLint align) override;

    void setDataInner(std::size_t size, const void *data, GLenum usage,
                      GLint align);

    [[nodiscard]] GLint getAlign() const override;
    [[nodiscard]] GLint getStride() const override;

    ~OGLVertexBuffer() override;

    OGLVertexBuffer(OGLVertexBuffer &&other) noexcept
        : VBO(other.VBO),
          stride(other.stride),
          align(other.align) {
        other.VBO    = 0;
        other.stride = 0;
        other.align  = 0;
    }

    OGLVertexBuffer &operator=(OGLVertexBuffer &&other) noexcept {
        if (this != &other) {
            VBO          = other.VBO;
            stride       = other.stride;
            align        = other.align;
            other.VBO    = 0;
            other.stride = 0;
            other.align  = 0;
        }
        return *this;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_VERTEXBUFFER_HPP
