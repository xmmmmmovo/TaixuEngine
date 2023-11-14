//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
#define ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP

#include "glm/glm.hpp"

#include "raw_data.hpp"
#include "texture.hpp"

namespace taixu {

struct Material final {
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    glm::vec3 ambient{};
    glm::vec3 emissive{};
    float     opacity{1.0f};
    float     refracti{1.0f};
    float     shininess{32.0f};
    float     strength{1.0f};

    int wireframe{0};
    int twosided{0};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
