//
// Created by xmmmmmovo on 2023/4/25.
//
#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP

#include <stb_image.h>

#include "asset_data.hpp"

namespace taixu {

enum class TextureType { Diffuse, Specular, Normal, Height };

struct Texture final : public BaseAssetData {
    TextureType type;
    stbi_uc    *data{nullptr};

    ~Texture() {
        if (data) { stbi_image_free(data); }
    }
};

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_TEXTURE_HPP
