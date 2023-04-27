//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <assimp/BaseImporter.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "platform/os/path.hpp"
#include "raw_data/model.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

class AssetManager {
    PROTOTYPE(private, std::filesystem::path, asset_path);

private:
    std::unordered_map<std::string, Texture> _textures{};
    std::unordered_map<std::string, Model>   _models{};

    Mesh processMesh(aiMesh *mesh, const aiScene *scene,
                     std::filesystem::path const &directory_path);

    void processNode(aiNode *node, const aiScene *scene, Model &model);

    Texture *processTexture(aiMaterial *material, aiTextureType type,
                            std::filesystem::path const &directory_path);

public:
    Model *loadModel(std::filesystem::path const &relative_path);

    // TODO: load model async
    void
    loadModelAsync(std::filesystem::path const &relative_path,
                   std::function<void(std::optional<Model>)> const &callback);

    Texture *loadTexture(std::filesystem::path const &relative_path,
                         TextureType                  type);

    // TODO: load texture async
    void loadTextureAsync(
            std::filesystem::path const                       &relative_path,
            std::function<void(std::optional<Texture>)> const &callback);

    void reset(std::filesystem::path const &asset_path) {
        _asset_path = asset_path;
        _textures.clear();
        _models.clear();
    }
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
