//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include "assimp/BaseImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "spdlog/spdlog.h"
#include <filesystem>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "platform/os/path.hpp"
#include "resource/json/json_type/game_object_json.hpp"
#include "resource/json/json_type/level_json.hpp"
#include "resource/json/json_type/mesh_json.hpp"
#include "resource/json/json_type/rigid_body_json.hpp"
#include "resource/json/json_type/transform_json.hpp"
#include "resource/json/json_type/world_json.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/model.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

class AssetManager final {
private:
    std::unordered_map<std::string, Texture2DAsset> _textures{};
    std::unordered_map<std::string, Model>          _models{};

    static Mesh processMesh(aiMesh *mesh);

    void processNode(aiNode *node, aiScene const *scene, Model &model);

    void processMaterial(aiScene const               *scene,
                         std::filesystem::path const &root_path, Model &model);

    Texture2DAsset *processTexture(aiMaterial *material, aiTextureType type,
                                   std::filesystem::path const &root_path,
                                   std::filesystem::path const &directory_path);

public:
    Model *loadModel(std::filesystem::path const &root_path,
                     std::filesystem::path const &relative_path);

    // TODO: load model async
    void loadModelAsync(std::filesystem::path const        &root_path,
                        std::filesystem::path const        &relative_path,
                        std::function<void(Model *)> const &callback);

    Texture2DAsset *loadTexture(std::filesystem::path const &root_path,
                                std::filesystem::path const &relative_path,
                                TextureType                  type);

    // TODO: load texture async
    void
    loadTextureAsync(std::filesystem::path const                 &root_path,
                     std::filesystem::path const                 &relative_path,
                     std::function<void(Texture2DAsset *)> const &callback);

    void reset() {
        _textures.clear();
        _models.clear();
    }

    std::unique_ptr<JsonWorld> _world;
    std::unique_ptr<JsonWorld> taixuworld;
    void loadWorld(std::filesystem::path const &file_path);
    void witeWorld(std::filesystem::path const &root_path);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
