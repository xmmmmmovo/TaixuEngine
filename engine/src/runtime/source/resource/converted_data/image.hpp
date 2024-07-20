/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <assimp/material.h>
#include <cstdlib>

#include "common/base/macro.hpp"

namespace taixu {

enum class EnumTextureType : std::uint8_t {
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

TX_INLINE EnumTextureType textureTypeFromAssimpType(const aiTextureType aitype) {
    switch (aitype) {
        case aiTextureType_DIFFUSE:
            return EnumTextureType::DIFFUSE;
        case aiTextureType_SPECULAR:
            return EnumTextureType::SPECULAR;
        case aiTextureType_NORMALS:
            return EnumTextureType::NORMAL;
        case aiTextureType_HEIGHT:
            return EnumTextureType::HEIGHT;
        case aiTextureType_DISPLACEMENT:
            return EnumTextureType::DISPLACEMENT;
        case aiTextureType_AMBIENT:
            return EnumTextureType::AMBIENT;
        case aiTextureType_EMISSIVE:
            return EnumTextureType::EMISSIVE;
        case aiTextureType_SHININESS:
            return EnumTextureType::SHININESS;
        case aiTextureType_OPACITY:
            return EnumTextureType::OPACITY;
        case aiTextureType_LIGHTMAP:
            return EnumTextureType::LIGHTMAP;
        case aiTextureType_BASE_COLOR:
            return EnumTextureType::BASE_COLOR;
        case aiTextureType_METALNESS:
            return EnumTextureType::METALLIC;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            return EnumTextureType::ROUGHNESS;
        case aiTextureType_AMBIENT_OCCLUSION:
            return EnumTextureType::AO;
        case aiTextureType_EMISSION_COLOR:
            return EnumTextureType::EMISSIVE_FACTOR;
        default:
            return EnumTextureType::DIFFUSE;
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
