//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
#define ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP

#include <glm/glm.hpp>

#include "asset_data.hpp"

namespace taixu {

struct Material final {
    glm::vec3 ambient{0.0f, 0.0f, 0.0f};
    glm::vec3 diffuse{0.0f, 0.0f, 0.0f};
    glm::vec3 specular{0.0f, 0.0f, 0.0f};
    float     shininess{0.0f};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
