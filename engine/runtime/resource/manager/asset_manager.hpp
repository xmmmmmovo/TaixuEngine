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

#include "glm/gtc/type_ptr.hpp"
#include "platform/os/path.hpp"
#include "resource/json/json_type/game_object_json.hpp"
#include "resource/json/json_type/level_json.hpp"
#include "resource/json/json_type/renderable_json.hpp"
#include "resource/json/json_type/rigid_body_json.hpp"
#include "resource/json/json_type/transform_json.hpp"
#include "resource/json/json_type/world_json.hpp"
#include "resource/raw_data/fbx_data.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/model.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

class AssetManager final {
private:
    std::unordered_map<const char *, Texture2DAsset> _textures{};
    std::unordered_map<const char *, Model>          _models{};
    std::unordered_map<const char *, FBXData>        _fbx_files{};
    std::unique_ptr<JsonWorld>                       _taixu_world;

    static Mesh processMesh(aiMesh *mesh);

    void processNode(aiNode *node, aiScene const *scene, Model &model);
    void processNode(aiNode *node, aiScene const *scene, Model &model,
                     FBXData *fbx);

    Mesh processSkinnedMesh(aiMesh *mesh, aiScene const *scene, FBXData *fbx);

    void processWeights(std::vector<glm::ivec4> &ids,
                        std::vector<glm::vec4>  &weights,
                        //const std::vector<std::uint32_t>&indices,
                        aiMesh *mesh, const aiScene *scene,
                        std::map<string, BoneInfo> &boneInfoMap,
                        int                        &boneCount);

    void processMaterial(aiScene const               *scene,
                         std::filesystem::path const &root_path, Model &model);

    Texture2DAsset *processTexture(aiMaterial *material, aiTextureType type,
                                   std::filesystem::path const &root_path,
                                   std::filesystem::path const &directory_path);

    static inline glm::mat4 convertMatrixToGlmFormat(const aiMatrix4x4 &from) {
        glm::mat4 to;
        //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        to[0][0] = from.a1;
        to[1][0] = from.a2;
        to[2][0] = from.a3;
        to[3][0] = from.a4;
        to[0][1] = from.b1;
        to[1][1] = from.b2;
        to[2][1] = from.b3;
        to[3][1] = from.b4;
        to[0][2] = from.c1;
        to[1][2] = from.c2;
        to[2][2] = from.c3;
        to[3][2] = from.c4;
        to[0][3] = from.d1;
        to[1][3] = from.d2;
        to[2][3] = from.d3;
        to[3][3] = from.d4;
        return to;
    }

    Bone generateBone(std::string name, int id, const aiNodeAnim *channel);

    void ReadMissingBones(const aiAnimation *animation, FBXData *fbx);

    void ReadHierarchyData(AssimpNodeData &dest, const aiNode *src);

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

    //for animation
    FBXData *loadFBX(std::filesystem::path const &root_path,
                     std::filesystem::path const &relative_path);

    void reset() {
        _textures.clear();
        _models.clear();
        _fbx_files.clear();
        _taixu_world.reset();
    }

    JsonWorld *loadWorld(std::filesystem::path const &file_path);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
