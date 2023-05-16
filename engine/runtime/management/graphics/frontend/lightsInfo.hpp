#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP

#include <glm/glm.hpp>

namespace taixu {

struct LightsInfo {
    glm::vec4 light_position;
    glm::vec4 light_color;
    glm::vec4 camera_position;
};

}// namespace taixu
#endif /* ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP */
