//
// Created by xmmmmmovo on 2023/2/21.
//

#ifndef TAIXUENGINE_OGLSHADER_HPP
#define TAIXUENGINE_OGLSHADER_HPP

#include <glad/glad.h>

#include <spdlog/spdlog.h>

#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "graphics/render/shader.hpp"

namespace taixu {


class OGLShader : public IShader {
private:
    /**
     * @brief
     */
    char const *_source;
    /**
     * @brief
     */
    GLenum      _shader_type;

public:
    /**
     * @brief
     * @param source
     * @param type
     */
    OGLShader(char const *source, ShaderTypeEnum type);

    /**
     * @brief release shader memory
     */
    ~OGLShader() override {
        if (_id != 0) { glDeleteShader(_id); }
    }
};

class OGLShaderProgram : public IShaderProgram {
public:
    OGLShaderProgram(char const *vertex_shader, char const *fragment_shader);

    ~OGLShaderProgram() override {
        if (_id != 0) { glDeleteProgram(_id); }
    }

    void use() const noexcept override { glUseProgram(_id); }

    void set_uniform(std::string_view name,
                     bool             value) const noexcept override {
        glUniform1i(glGetUniformLocation(_id, name.data()),
                    static_cast<int>(value));
    };

    void set_uniform(std::string_view name, int value) const noexcept override {
        glUniform1i(glGetUniformLocation(_id, name.data()), value);
    };

    void set_uniform(std::string_view name,
                     float            value) const noexcept override {
        glUniform1f(glGetUniformLocation(_id, name.data()), value);
    };

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec2       &value) const noexcept override {
        glUniform2fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }

    void set_uniform(const std::string_view name, float x,
                     float y) const noexcept override {
        glUniform2f(glGetUniformLocation(_id, name.data()), x, y);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec3       &value) const noexcept override {
        glUniform3fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }

    void set_uniform(const std::string_view name, float x, float y,
                     float z) const noexcept override {
        glUniform3f(glGetUniformLocation(_id, name.data()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec4       &value) const noexcept override {
        glUniform4fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }
    void set_uniform(const std::string_view name, float x, float y, float z,
                     float w) const noexcept override {
        glUniform4f(glGetUniformLocation(_id, name.data()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat2       &mat) const noexcept override {
        glUniformMatrix2fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat3       &mat) const noexcept override {
        glUniformMatrix3fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat4       &mat) const noexcept override {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }
};

}// namespace taixu

#endif//TAIXUENGINE_OGLSHADER_HPP
