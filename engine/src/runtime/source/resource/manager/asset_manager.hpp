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

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

namespace taixu {

class AssetManager final {
    // private:
    //     static Mesh processMesh(aiMesh* mesh);
    //
    //     void processNode(aiNode* node, aiScene const* scene, Model& model);
    //
    //
    //     void processMaterial(aiScene const*               scene,
    //                          std::filesystem::path const& root_path, Model&
    //                          model);
    //
    //     Texture2DAsset* processTexture(aiMaterial* material, aiTextureType
    //     type,
    //                                    std::filesystem::path const&
    //                                    root_path, std::filesystem::path
    //                                    const& directory_path);
    //
    // public:
    //     Model* loadModel(std::filesystem::path const& root_path,
    //                      std::filesystem::path const& relative_path);
    //
    //     Texture2DAsset* loadTexture(std::filesystem::path const& root_path,
    //                                 std::filesystem::path const&
    //                                 relative_path, TextureType type =
    //                                 TextureType::COMMON);
};
}// namespace taixu

#endif// TAIXUENGINE_RESOURCE_MANAGER_HPP
