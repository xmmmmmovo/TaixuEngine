/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <assimp/material.h>
#include <stb_image.h>

#include "taixu/common/base/macro.hpp"

namespace taixu {

enum class TextureType : std::uint8_t {
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

TX_INLINE TextureType textureTypeFromAssimpType(const aiTextureType aitype) {
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


struct Image final : public std::enable_shared_from_this<Image> {
    // ignore
    std::shared_ptr<uint8_t[]> data{nullptr};// NOLINT
    uint32_t                   size{0};
    uint32_t                   w{0};
    uint32_t                   h{0};
    uint32_t                   channels{0};
    uint32_t                   desired_channels{0};
    bool                       is_hdr{false};
    bool                       is_srgb{false};
    bool                       is_cube{false};
};

}// namespace taixu
