//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_RENDER_TYPES_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_RENDER_TYPES_HPP

#include <glm/glm.hpp>
#include <variant>

namespace taixu {

using uniform_t =
        std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

}

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_RENDER_RENDER_TYPES_HPP
