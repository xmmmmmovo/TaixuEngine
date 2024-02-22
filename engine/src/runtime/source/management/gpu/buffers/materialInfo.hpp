#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATERIALINFO_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATERIALINFO_HPP

#include <glm/glm.hpp>

namespace taixu {

struct MaterialInfo {
    glm::vec4 ambient{};
    glm::vec4 diffuse{};
    glm::vec4 specular{};
    glm::vec4 emissive{};
    float     shininess{0.0f};
};

}// namespace taixu
#endif /* ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATERIALINFO_HPP */
