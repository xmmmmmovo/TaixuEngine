//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP

#include "asset_data.hpp"
#include "core/base/macro.hpp"
#include "resource/raw_data/mesh.hpp"
#include <vector>


namespace taixu {

struct Model final : public BaseAssetData {
    std::vector<Mesh> meshes;
};

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
