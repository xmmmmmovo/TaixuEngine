#ifndef ENGINE_RUNTIME_GRAPHICS_SHADER
#define ENGINE_RUNTIME_GRAPHICS_SHADER

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "spdlog/spdlog.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace taixu::cg {

class Shader {
public:
    explicit Shader(char const *content);
    // do not copy
    Shader(const Shader &)            = delete;
    Shader &operator=(const Shader &) = delete;

    Shader(Shader &&other) noexcept            = default;
    Shader &operator=(Shader &&other) noexcept = default;

    ~Shader() {
        if (_id != 0) { glDeleteShader(_id); }
    };

    // compile time value
    [[nodiscard]] constexpr unsigned get_id() const noexcept { return _id; }

protected:
    unsigned int _id;
    char const  *_source;
};

class VertexShader : public Shader {
public:
    explicit VertexShader(char const *content);
};

class FragmentShader : public Shader {
public:
    explicit FragmentShader(char const *content);
};

class ShaderProgram {
public:
    ShaderProgram(char const *vertex_shader, char const *fragment_shader)
        : _id{0} {
        VertexShader   vertex{vertex_shader};
        FragmentShader fragment{fragment_shader};

        _id = glCreateProgram();
        glAttachShader(_id, vertex.get_id());
        glAttachShader(_id, fragment.get_id());
        glLinkProgram(_id);

        int  success{};
        char log_info[512];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(_id, 512, nullptr, log_info);
            spdlog::error("ERROR:SHADER::PROGRAM::LINK_FAILED\n{}", log_info);
        }
    };

    ~ShaderProgram() {
        if (_id != 0) { glDeleteProgram(_id); }
    };

    void use() const noexcept { glUseProgram(_id); };

    void set_uniform(std::string_view name, bool value) const noexcept {
        glUniform1i(glGetUniformLocation(_id, name.data()),
                    static_cast<int>(value));
    };

    void set_uniform(std::string_view name, int value) const noexcept {
        glUniform1i(glGetUniformLocation(_id, name.data()), value);
    };

    void set_uniform(std::string_view name, float value) const noexcept {
        glUniform1f(glGetUniformLocation(_id, name.data()), value);
    };

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec2       &value) const noexcept {
        glUniform2fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }

    void set_uniform(const std::string_view name, float x,
                     float y) const noexcept {
        glUniform2f(glGetUniformLocation(_id, name.data()), x, y);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec3       &value) const noexcept {
        glUniform3fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }

    void set_uniform(const std::string_view name, float x, float y,
                     float z) const noexcept {
        glUniform3f(glGetUniformLocation(_id, name.data()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::vec4       &value) const noexcept {
        glUniform4fv(glGetUniformLocation(_id, name.data()), 1, &value[0]);
    }
    void set_uniform(const std::string_view name, float x, float y, float z,
                     float w) const noexcept {
        glUniform4f(glGetUniformLocation(_id, name.data()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat2       &mat) const noexcept {
        glUniformMatrix2fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat3       &mat) const noexcept {
        glUniformMatrix3fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void set_uniform(const std::string_view name,
                     const glm::mat4       &mat) const noexcept {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.data()), 1, GL_FALSE,
                           &mat[0][0]);
    }

private:
    unsigned int _id;
};
}// namespace taixu::cg

#endif /* ENGINE_RUNTIME_GRAPHICS_SHADER */
