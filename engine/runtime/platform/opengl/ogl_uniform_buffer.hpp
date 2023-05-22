//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_UNIFORM_BUFFER_HPP
#define ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_UNIFORM_BUFFER_HPP

#include "glm/gtc/type_ptr.hpp"
#include "management/graphics/render/uniform_buffer.hpp"

#include <glad/glad.h>
#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>

namespace taixu {

class OGLUniformBuffer : public IUniformBuffer {
    std::uint32_t _id{0};

public:
    OGLUniformBuffer() { glGenBuffers(1, &_id); }

    void bind() override { glBindBuffer(GL_UNIFORM_BUFFER, _id); }

    template<typename OBJ>
    void setData(const OBJ &obj, std::uint32_t idx) {
        glBufferData(GL_UNIFORM_BUFFER, sizeof(obj), &obj, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, idx, _id);
    }

    template<typename Data>
    void updateData(Data const &data, std::size_t offset = 0) {
        glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(data), &data);
    }

    void unbind() override { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

    [[nodiscard]] std::uint32_t getbufferID() const { return _id; };

    ~OGLUniformBuffer() override { glDeleteBuffers(1, &_id); }
};
}// namespace taixu

#endif//ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_UNIFORM_BUFFER_HPP
