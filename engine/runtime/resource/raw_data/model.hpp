//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
#define TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP

#include "mesh.hpp"
#include "resource/raw_data/asset_data.hpp"

#include <memory>
#include <vector>

namespace taixu {

struct ModelGPU final {
    std::vector<MeshGPU> meshes{};
};

struct Model final : public BaseAssetData {
    std::vector<Mesh>     meshes;
    std::vector<Material> materials;

    std::optional<ModelGPU> gpu_data{std::nullopt};
};

inline void transferCPUModelToGPU(Model *model) {
    ModelGPU ret{};

    ret.meshes.reserve(model->meshes.size());
    for (auto const &mesh : model->meshes) {
        ret.meshes.push_back(transferCPUMesh2GPU(mesh));
    }

    model->gpu_data = std::move(ret);
}

}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_RAW_DATA_MODEL_HPP
