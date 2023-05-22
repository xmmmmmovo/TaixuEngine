#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP

#include <glm/glm.hpp>

namespace taixu {

static constexpr int MAX_LIGHTS = 4;

struct DirLight {
    glm::vec4 direction;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

struct PointLight {
    glm::vec4 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

struct SpotLight {
    glm::vec4 position;
    glm::vec4 direction;
    float     cutOff;
    float     outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

struct LightsInfo {
    int dirLightCount{0};
    int pointLightCount{0};
    int spotLightCount{0};

    std::array<DirLight, MAX_LIGHTS>   dirLights{};
    std::array<PointLight, MAX_LIGHTS> pointLights{};
    std::array<SpotLight, MAX_LIGHTS>  spotLights{};
};

}// namespace taixu
#endif /* ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_LIGHTSINFO_HPP */
