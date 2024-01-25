//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP

#include "mesh.hpp"
#include "raw_data.hpp"

#include <memory>
#include <vector>

namespace taixu {

struct OBJModel final : public AbstractAssetData {
    std::vector<Mesh>     meshes;
    std::vector<Material> materials;
};

struct FBXModel final : public AbstractAssetData {};

}// namespace taixu

#endif// TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
