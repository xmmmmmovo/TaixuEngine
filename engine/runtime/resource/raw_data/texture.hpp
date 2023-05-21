//
// Created by xmmmmmovo on 2023/4/25.
//
#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP

#include <assimp/material.h>
#include <memory>
#include <stb_image.h>

#include "asset_data.hpp"
#include "management/graphics/render/texture_2d.hpp"
#include "platform/opengl/ogl_texture2d.hpp"
#include "platform/os/path.hpp"

namespace taixu {

enum class TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
    DISPLACEMENT,

    AMBIENT,
    EMISSIVE,
    SHININESS,
    OPACITY,
    LIGHTMAP,

    BASE_COLOR,
    METALLIC,
    ROUGHNESS,
    AO,
    EMISSIVE_FACTOR,

    COMMON
};

inline TextureType textureTypeFromAssimpType(aiTextureType aitype) {
    switch (aitype) {
        case aiTextureType_DIFFUSE:
            return TextureType::DIFFUSE;
        case aiTextureType_SPECULAR:
            return TextureType::SPECULAR;
        case aiTextureType_NORMALS:
            return TextureType::NORMAL;
        case aiTextureType_HEIGHT:
            return TextureType::HEIGHT;
        case aiTextureType_DISPLACEMENT:
            return TextureType::DISPLACEMENT;
        case aiTextureType_AMBIENT:
            return TextureType::AMBIENT;
        case aiTextureType_EMISSIVE:
            return TextureType::EMISSIVE;
        case aiTextureType_SHININESS:
            return TextureType::SHININESS;
        case aiTextureType_OPACITY:
            return TextureType::OPACITY;
        case aiTextureType_LIGHTMAP:
            return TextureType::LIGHTMAP;
        case aiTextureType_BASE_COLOR:
            return TextureType::BASE_COLOR;
        case aiTextureType_METALNESS:
            return TextureType::METALLIC;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            return TextureType::ROUGHNESS;
        case aiTextureType_AMBIENT_OCCLUSION:
            return TextureType::AO;
        case aiTextureType_EMISSION_COLOR:
            return TextureType::EMISSIVE_FACTOR;
        default:
            return TextureType::DIFFUSE;
    }
}

struct Texture2DAsset final : public BaseAssetData {
    TextureType                 type{TextureType::DIFFUSE};
    std::unique_ptr<ITexture2D> texture{nullptr};
};

inline Texture2DAsset
transferCPUTextureToGPU(std::filesystem::path const &asset_path,
                        std::filesystem::path const &relative_path,
                        TextureType                  type) {
    Texture2DAsset texture{};

    texture.type      = type;
    texture.file_path = relative_path;

    if (EngineArgs::getInstance().api == GraphicsAPI::OPENGL) {
        texture.texture = std::make_unique<OGLTexture2D>(
                fromRelativePath(asset_path, relative_path));
    }
    return texture;
}

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
