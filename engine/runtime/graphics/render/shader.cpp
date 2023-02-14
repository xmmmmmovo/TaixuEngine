#include "shader.hpp"
#include <ostream>

namespace taixu::cg {

Shader::Shader(char const *content) : _id{0}, _source(content) {}

VertexShader::VertexShader(char const *content) : Shader{content} {
    _id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_id, 1, &_source, nullptr);
    glCompileShader(_id);

    int  success{};
    char log[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_id, 512, nullptr, log);
        spdlog::error("ERROR:SHADER::VERTEX::COMPILEATION_FAILED\n{}", log);
    }
};

FragmentShader::FragmentShader(char const *content) : Shader{content} {
    _id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_id, 1, &_source, nullptr);
    glCompileShader(_id);

    int  success{};
    char log[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_id, 512, nullptr, log);
        spdlog::error("ERROR:SHADER::FRAGMENT::COMPILEATION_FAILED\n{}", log);
    }
};

}// namespace taixu::cg