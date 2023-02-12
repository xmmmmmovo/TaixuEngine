#include "shader.hpp"
#include <ostream>

namespace taixu::cg {

Shader::Shader(std::string_view const &file_path) : _id{0} {
    std::ifstream fs{};
    fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        fs.open(std::string{file_path});
        std::stringstream ss{};
        ss << fs.rdbuf();
        fs.close();
        _source = ss.str();
    } catch (std::ifstream::failure &e) {
        spdlog::error("Error::Shader::File_Not_Successfully_Read");
    }
}

VertexShader::VertexShader(std::string_view const &file_path)
    : Shader{std::move(file_path)} {
    _id             = glCreateShader(GL_VERTEX_SHADER);
    auto source_str = _source.c_str();
    glShaderSource(_id, 1, &source_str, nullptr);
    glCompileShader(_id);

    int  success{};
    char log[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_id, 512, nullptr, log);
        spdlog::error("ERROR:SHADER::VERTEX::COMPILEATION_FAILED\n{}", log);
    }
};

FragmentShader::FragmentShader(std::string_view const &file_path)
    : Shader{file_path} {
    _id             = glCreateShader(GL_FRAGMENT_SHADER);
    auto source_str = _source.c_str();
    glShaderSource(_id, 1, &source_str, nullptr);
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