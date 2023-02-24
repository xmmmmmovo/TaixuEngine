//
// Created by xmmmmmovo on 2023/2/23.
//
#include "OGLShader.hpp"

#include "core/base/macro.hpp"

namespace taixu {

GLenum mapToShaderTypeGLenum(ShaderTypeEnum type) {
    switch (type) {
        case VERTEX:
            return GL_VERTEX_SHADER;
        case FRAGMENT:
            return GL_FRAGMENT_SHADER;
        case COMPUTE: {
#ifdef GL_COMPUTE_SHADER
            return GL_COMPUTE_SHADER
#else
            return 0;
#endif
        }
        case TESS_CONTROL:
            return GL_TESS_CONTROL_SHADER;
        case TESS_EVALUATION:
            return GL_TESS_EVALUATION_SHADER;
        case GEOMETRY:
            return GL_GEOMETRY_SHADER;
    }
    return 0;
}

std::string_view mapToShaderTypeString(ShaderTypeEnum type) {
    switch (type) {
        case VERTEX:
            return "GL_VERTEX_SHADER";
        case FRAGMENT:
            return "GL_FRAGMENT_SHADER";
        case COMPUTE:
            return "GL_COMPUTE_SHADER";
        case TESS_CONTROL:
            return "GL_TESS_CONTROL_SHADER";
        case TESS_EVALUATION:
            return "GL_TESS_EVALUATION_SHADER";
        case GEOMETRY:
            return "GL_GEOMETRY_SHADER";
    }
    return "unknown";
}

OGLShader::OGLShader(const char *source, ShaderTypeEnum type)
    : _source(source),
      _shader_type(mapToShaderTypeGLenum(type)) {
    _id = glCreateShader(_shader_type);
    glShaderSource(_id, 1, &_source, nullptr);
    glCompileShader(_id);

    int success{};
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(_id, 512, nullptr, log);
        spdlog::error("ERROR:SHADER::{}::COMPILATION_FAILED\n{}",
                      mapToShaderTypeString(type), log);
    }
}

OGLShaderProgram::OGLShaderProgram(const char *vertex_shader,
                                   const char *fragment_shader) {
    OGLShader vertex{vertex_shader, ShaderTypeEnum::VERTEX};
    OGLShader fragment{fragment_shader, ShaderTypeEnum::FRAGMENT};

    _id = glCreateProgram();
    glAttachShader(_id, vertex.get_id());
    glAttachShader(_id, fragment.get_id());
    glLinkProgram(_id);

    int success{};
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        char log_info[512];
        glGetProgramInfoLog(_id, 512, nullptr, log_info);
        spdlog::error("ERROR:SHADER::PROGRAM::LINK_FAILED\n{}", log_info);
    }
}

}// namespace taixu
