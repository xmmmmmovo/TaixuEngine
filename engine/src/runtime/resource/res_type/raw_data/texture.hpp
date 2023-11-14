//
// Created by xmmmmmovo on 2023/4/25.
//
#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP

#include "assimp/material.h"
#include <common/utils/pointer_utils.hpp>
#include <memory>

#include "raw_data.hpp"
#include "runtime/engine_args.hpp"
#include "runtime/platform/os/path.hpp"

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

struct Image final {
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
