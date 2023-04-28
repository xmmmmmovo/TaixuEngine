//
// Created by xmmmmmovo on 2023/4/25.
//
#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP

#include <stb_image.h>

#include "asset_data.hpp"

namespace taixu {

enum class TextureType {
    Diffuse,
    Specular,
    Normal,
    Height,
    Displacement,

    Ambient,
    Emissive,
    Shininess,
    Opacity,
    Lightmap,

    BaseColor,
    Metallic,
    Roughness,
    AO,
    EmissiveFactor,
};

struct Texture final : public BaseAssetData {
    TextureType type{TextureType::Diffuse};
    stbi_uc    *data{nullptr};

    explicit Texture() = default;

    // move constructor
    Texture(Texture &&other) noexcept : type(other.type), data(other.data) {
        other.data = nullptr;
        file_path  = other.file_path;
    }

    // move assignment
    Texture &operator=(Texture &&other) noexcept {
        if (this == &other) { return *this; }
        type       = other.type;
        data       = other.data;
        file_path  = other.file_path;
        other.data = nullptr;
        return *this;
    }

    ~Texture() {
        if (data) { stbi_image_free(data); }
    }
};

inline TextureType textureTypeFromAssimpType(aiTextureType aitype) {
    switch (aitype) {
        case aiTextureType_DIFFUSE:
            return TextureType::Diffuse;
        case aiTextureType_SPECULAR:
            return TextureType::Specular;
        case aiTextureType_NORMALS:
            return TextureType::Normal;
        case aiTextureType_HEIGHT:
            return TextureType::Height;
        case aiTextureType_DISPLACEMENT:
            return TextureType::Displacement;
        case aiTextureType_AMBIENT:
            return TextureType::Ambient;
        case aiTextureType_EMISSIVE:
            return TextureType::Emissive;
        case aiTextureType_SHININESS:
            return TextureType::Shininess;
        case aiTextureType_OPACITY:
            return TextureType::Opacity;
        case aiTextureType_LIGHTMAP:
            return TextureType::Lightmap;
        case aiTextureType_BASE_COLOR:
            return TextureType::BaseColor;
        case aiTextureType_METALNESS:
            return TextureType::Metallic;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            return TextureType::Roughness;
        case aiTextureType_AMBIENT_OCCLUSION:
            return TextureType::AO;
        case aiTextureType_EMISSION_COLOR:
            return TextureType::EmissiveFactor;
        default:
            return TextureType::Diffuse;
    }
}

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
