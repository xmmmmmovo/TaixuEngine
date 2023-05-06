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
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    glm::vec3 ambient{};
    glm::vec3 emissive{};
    float     opacity{1.0f};
    float     refracti{1.0f};
    float     shininess{1.0f};
    float     strength{1.0f};

    int wireframe{0};
    int twosided{0};

    // legacy & PBR
    Texture2D *diffuse_tex{nullptr};
    Texture2D *specular_tex{nullptr};
    // normal mapping Texture2D
    Texture2D *normal_tex{nullptr};
    Texture2D *height_tex{nullptr};
    Texture2D *displacement_tex{nullptr};

    // lagacy
    Texture2D *ambient_tex{nullptr};
    Texture2D *emissive_tex{nullptr};
    Texture2D *shininess_tex{nullptr};
    Texture2D *opacity_tex{nullptr};
    Texture2D *lightmap_tex{nullptr};

    // PBR
    Texture2D *base_color_tex{nullptr};
    Texture2D *metallic_tex{nullptr};
    Texture2D *roughness_tex{nullptr};
    Texture2D *ao_tex{nullptr};
    Texture2D *emissive_factor_tex{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
