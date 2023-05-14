//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_SHADER_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_SHADER_MANAGER_HPP

#include "render/shader.hpp"

#include <unordered_map>
#include <vector>

namespace taixu {

class ShaderManager final {
private:
    std::unordered_map<std::uint64_t, std::unique_ptr<IShaderProgram>> _shaders;

public:
    void addShader(std::uint64_t id, std::unique_ptr<IShaderProgram> shader) {
        _shaders[id] = std::move(shader);
    }

    void removeShader(std::uint64_t id) {
        if (contains(id)) { _shaders.erase(id); }
    }

    IShaderProgram *getShader(std::uint64_t id) {
        if (contains(id)) { return _shaders[id].get(); }
        return nullptr;
    }

    bool contains(std::uint64_t id) { return _shaders.count(id); }

    void clear() { _shaders.clear(); }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_SHADER_MANAGER_HPP
