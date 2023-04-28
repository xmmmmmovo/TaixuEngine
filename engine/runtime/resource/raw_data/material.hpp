//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
#define ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP

#include <glm/glm.hpp>

#include "asset_data.hpp"
#include "texture.hpp"

namespace taixu {

struct Material final {
    glm::vec3 ambient{};
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    glm::vec3 emissive{};
    float     opacity{1.0f};
    float     refracti{1.0f};
    float     shininess{1.0f};
    float     strength{1.0f};

    int wireframe{0};
    int twosided{0};

    // legacy & PBR
    Texture *diffuse_tex{nullptr};
    Texture *specular_tex{nullptr};
    // normal mapping texture
    Texture *normal_tex{nullptr};
    Texture *height_tex{nullptr};
    Texture *displacement_tex{nullptr};

    // lagacy
    Texture *ambient_tex{nullptr};
    Texture *emissive_tex{nullptr};
    Texture *shininess_tex{nullptr};
    Texture *opacity_tex{nullptr};
    Texture *lightmap_tex{nullptr};

    // PBR
    Texture *base_color_tex{nullptr};
    Texture *metallic_tex{nullptr};
    Texture *roughness_tex{nullptr};
    Texture *ao_tex{nullptr};
    Texture *emissive_factor_tex{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
