//
// Created by xmmmmmovo on 11/12/2023.
//

#ifndef ENGINE_SRC_RUNTIME_RESOURCE_HELPER_ASSET_HELPER_5EEA3287A5964C3185EB6F0F11B371A4
#define ENGINE_SRC_RUNTIME_RESOURCE_HELPER_ASSET_HELPER_5EEA3287A5964C3185EB6F0F11B371A4

namespace taixu {

constexpr std::string_view ASSET_MAGIC_NUMBER = "MURASAME";
constexpr std::uint32_t    ASSET_VERSION      = 1;

enum class EnumAssetType : std::uint8_t {
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
    EnumAssetType type{EnumAssetType::UNKNOWN};
    std::uint32_t size{0};
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_RESOURCE_HELPER_ASSET_HELPER_5EEA3287A5964C3185EB6F0F11B371A4
