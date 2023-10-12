//
// Created by xmmmmmovo on 2023/7/24.
//

#ifndef ENGINE_SRC_RUNTIME_RESOURCE_MANAGER_ASSET_CONVERTER_HPP
#define ENGINE_SRC_RUNTIME_RESOURCE_MANAGER_ASSET_CONVERTER_HPP

namespace taixu {

constexpr std::string_view ASSET_MAGIC_NUMBER = "MURASAME_WAIFU_";
constexpr std::string_view ASSET_VERSION      = "0.0.1";

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
    AssetType type{AssetType::UNKNOWN};
    std::uint32_t  size{0};
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_RESOURCE_MANAGER_ASSET_CONVERTER_HPP
