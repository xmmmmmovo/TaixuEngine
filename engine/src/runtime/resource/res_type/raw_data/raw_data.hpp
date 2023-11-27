//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_ASSET_DATA_HPP
#define TAIXUENGINE_ASSET_DATA_HPP

#include <filesystem>

#include "base/macro.hpp"

namespace taixu {

struct AbstractAssetData {
    std::filesystem::path file_path;
};

}// namespace taixu

#endif// TAIXUENGINE_ASSET_DATA_HPP
