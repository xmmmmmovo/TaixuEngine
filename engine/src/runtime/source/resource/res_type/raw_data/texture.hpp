//
// Created by xmmmmmovo on 2023/4/25.
//
#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP

#include "assimp/material.h"
#include "common/utils/pointer_utils.hpp"
#include <memory>

#include "platform/os/path.hpp"
#include "raw_data.hpp"

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

inline EnumTextureType textureTypeFromAssimpType(aiTextureType aitype) {
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

struct Image final : std::enable_shared_from_this<Image> {
    uint8_t* data{nullptr};
    int32_t  size{0};
    int32_t  w{0};
    int32_t  h{0};
    int32_t  channels{0};
    int32_t  desired_channels{0};
    bool     is_hdr{false};
    bool     is_srgb{false};
    bool     is_cube{false};

    ~Image() { free(data); }
};

}// namespace taixu

#endif// TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
