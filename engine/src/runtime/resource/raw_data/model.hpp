//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP

#include "mesh.hpp"
#include <runtime/resource/raw_data/asset_data.hpp>

#include <memory>
#include <vector>

namespace taixu {

struct ModelGPU final {
    std::vector<MeshGPU> meshes{};
};

struct Model final : public AbstractAssetData {
    std::vector<Mesh>     meshes;
    std::vector<Material> materials;

    std::optional<ModelGPU> gpu_data{std::nullopt};
};

}// namespace taixu

#endif// TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
