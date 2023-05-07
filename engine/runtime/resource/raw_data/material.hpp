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
    Texture2DAsset *diffuse_tex{nullptr};
    Texture2DAsset *specular_tex{nullptr};
    // normal mapping Texture2D
    Texture2DAsset *normal_tex{nullptr};
    Texture2DAsset *height_tex{nullptr};
    Texture2DAsset *displacement_tex{nullptr};

    // lagacy
    Texture2DAsset *ambient_tex{nullptr};
    Texture2DAsset *emissive_tex{nullptr};
    Texture2DAsset *shininess_tex{nullptr};
    Texture2DAsset *opacity_tex{nullptr};
    Texture2DAsset *lightmap_tex{nullptr};

    // PBR
    Texture2DAsset *base_color_tex{nullptr};
    Texture2DAsset *metallic_tex{nullptr};
    Texture2DAsset *roughness_tex{nullptr};
    Texture2DAsset *ao_tex{nullptr};
    Texture2DAsset *emissive_factor_tex{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_RAW_DATA_MATERIAL_HPP
