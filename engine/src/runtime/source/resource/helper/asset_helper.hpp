//
// Created by xmmmmmovo on 11/12/2023.
//

#pragma once

#include "common/hal/tx_string.hpp"

namespace taixu {

constexpr tx_string_view ASSET_MAGIC_NUMBER = "MURASAME";
constexpr std::uint32_t  ASSET_VERSION      = 1;

enum class AssetType : std::uint8_t {
    TEXTURE,
    MATERIAL,
    MESH,
    SHADER,
    FONT,
    SOUND,
    MUSIC,
    WORLD,
    MANIFEST,
    UNKNOWN
};

struct AssetHeader {
    AssetType     type{AssetType::UNKNOWN};
    std::uint32_t size{0};
};

}// namespace taixu
