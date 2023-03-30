//
// Created by xmmmmmovo on 2023/2/25.
//

#ifndef TAIXUENGINE_OGLVERTEXBUFFER_HPP
#define TAIXUENGINE_OGLVERTEXBUFFER_HPP

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

    void setData(std::size_t size, const void *data, GLenum usage,
                 GLint align) override;

    void setDataInner(std::size_t size, const void *data, GLenum usage,
                      GLint align);

    [[nodiscard]] GLint getAlign() const override;
    [[nodiscard]] GLint getStride() const override;

    ~OGLVertexBuffer() override;

    OGLVertexBuffer(OGLVertexBuffer &&other) noexcept            = default;
    OGLVertexBuffer &operator=(OGLVertexBuffer &&other) noexcept = default;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLVERTEXBUFFER_HPP
