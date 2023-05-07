//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include "assimp/BaseImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "core/container/map_vector.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "platform/os/path.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/model.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

class AssetManager final {
    PROTOTYPE(private, std::filesystem::path, asset_path);

private:
    MapVector<std::string, Texture2DAsset> _textures{};
    MapVector<std::string, Model>          _models{};

    static Mesh processMesh(aiMesh *mesh);

    void processNode(aiNode *node, aiScene const *scene, Model &model);

    void processMaterial(aiScene const *scene, Model &model);

    Texture2DAsset *processTexture(aiMaterial *material, aiTextureType type,
                                   std::filesystem::path const &directory_path);

public:
    Model *loadModel(std::filesystem::path const &relative_path);

    // TODO: load model async
    void loadModelAsync(std::filesystem::path const        &relative_path,
                        std::function<void(Model *)> const &callback);

    Texture2DAsset *loadTexture(std::filesystem::path const &relative_path,
                                TextureType                  type);

    // TODO: load texture async
    void
    loadTextureAsync(std::filesystem::path const                 &relative_path,
                     std::function<void(Texture2DAsset *)> const &callback);

    void reset(std::filesystem::path const &asset_path) {
        _asset_path = asset_path;
        _textures.clear();
        _models.clear();
    }
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
