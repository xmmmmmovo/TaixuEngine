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
#include "resource/raw_data/fbx_data.hpp"

namespace taixu {

class AssetManager final {
private:
    std::unordered_map<std::string, Texture2DAsset> _textures{};
    std::unordered_map<std::string, Model>          _models{};
    std::unordered_map<std::string, FBXData>          _fbx_files{};

    static Mesh processMesh(aiMesh *mesh);

    void processNode(aiNode *node, aiScene const *scene, Model &model,bool skeleton);

    static Mesh processSkinnedMesh(aiMesh *mesh);

    void processWeights(std::vector<VertexRelateBoneInfo> &vbrs,
                                  aiMesh *mesh, const aiScene *scene, 
                                  std::map<string, BoneInfo> &boneInfoMap,
	                              int &boneCount);

    void processMaterial(aiScene const               *scene,
                         std::filesystem::path const &root_path, Model &model);

    Texture2DAsset *processTexture(aiMaterial *material, aiTextureType type,
                                   std::filesystem::path const &root_path,
                                   std::filesystem::path const &directory_path);

    static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}

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
    void writeWorld(std::filesystem::path const &root_path);


    //for animation
    FBXData * loadFBX(std::filesystem::path const &root_path,
                     std::filesystem::path const &relative_path);
    
    Bone processBoneAnimation(aiBone *b);

};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
