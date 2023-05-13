//
// Created by xmmmmmovo on 2023/2/18.
//

#include "assimp/material.h"
#include "assimp/scene.h"
#include <vector>

#include "asset_manager.hpp"
#include "resource/helper/image_helper.hpp"
#include "resource/raw_data/material.hpp"
#include "resource/raw_data/mesh.hpp"
#include "resource/raw_data/texture.hpp"

namespace taixu {

void AssetManager::processNode(aiNode *node, aiScene const *scene,
                               Model &model) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.emplace_back(processMesh(mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model);
    }
}

void AssetManager::processMaterial(aiScene const               *scene,
                                   std::filesystem::path const &root_path,
                                   Model                       &model) {
    model.materials.reserve(scene->mNumMaterials);
    for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
        auto      material = scene->mMaterials[i];
        Material  mat{};
        aiColor4D color{};

        // load material ids
        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color)) {
            mat.ambient = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
            mat.diffuse = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) {
            mat.specular = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color)) {
            mat.emissive = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &mat.shininess)) {
            mat.shininess /= 4.0f;
        }

        if (AI_SUCCESS ==
            aiGetMaterialFloat(material, AI_MATKEY_OPACITY, &mat.opacity)) {
            mat.opacity = 1.0f - mat.opacity;
        }

        if (AI_SUCCESS ==
            aiGetMaterialFloat(material, AI_MATKEY_REFRACTI, &mat.refracti)) {
            mat.refracti = 1.0f / mat.refracti;
        }

        if (AI_SUCCESS == aiGetMaterialFloat(material,
                                             AI_MATKEY_SHININESS_STRENGTH,
                                             &mat.strength)) {
            mat.strength /= 4.0f;
        }

        if (AI_SUCCESS == aiGetMaterialInteger(material,
                                               AI_MATKEY_ENABLE_WIREFRAME,
                                               &mat.wireframe)) {
            mat.wireframe = mat.wireframe ? 1 : 0;
        }

        if (AI_SUCCESS ==
            aiGetMaterialInteger(material, AI_MATKEY_TWOSIDED, &mat.twosided)) {
            mat.twosided = mat.twosided ? 1 : 0;
        }

        // load material textures
        mat.diffuse_tex =
                processTexture(material, aiTextureType_DIFFUSE, root_path,
                               model.file_path.parent_path());

        mat.specular_tex =
                processTexture(material, aiTextureType_SPECULAR, root_path,
                               model.file_path.parent_path());

        mat.normal_tex =
                processTexture(material, aiTextureType_NORMALS, root_path,
                               model.file_path.parent_path());

        mat.height_tex =
                processTexture(material, aiTextureType_HEIGHT, root_path,
                               model.file_path.parent_path());

        mat.displacement_tex =
                processTexture(material, aiTextureType_DISPLACEMENT, root_path,
                               model.file_path.parent_path());

        mat.ambient_tex =
                processTexture(material, aiTextureType_AMBIENT, root_path,
                               model.file_path.parent_path());

        mat.emissive_tex =
                processTexture(material, aiTextureType_EMISSIVE, root_path,
                               model.file_path.parent_path());

        mat.shininess_tex =
                processTexture(material, aiTextureType_SHININESS, root_path,
                               model.file_path.parent_path());

        mat.opacity_tex =
                processTexture(material, aiTextureType_OPACITY, root_path,
                               model.file_path.parent_path());

        mat.lightmap_tex =
                processTexture(material, aiTextureType_LIGHTMAP, root_path,
                               model.file_path.parent_path());

        // PBR
        mat.base_color_tex =
                processTexture(material, aiTextureType_BASE_COLOR, root_path,
                               model.file_path.parent_path());

        mat.metallic_tex =
                processTexture(material, aiTextureType_METALNESS, root_path,
                               model.file_path.parent_path());

        mat.roughness_tex =
                processTexture(material, aiTextureType_DIFFUSE_ROUGHNESS,
                               root_path, model.file_path.parent_path());

        mat.ao_tex = processTexture(material, aiTextureType_AMBIENT_OCCLUSION,
                                    root_path, model.file_path.parent_path());

        mat.emissive_factor_tex =
                processTexture(material, aiTextureType_EMISSION_COLOR,
                               root_path, model.file_path.parent_path());

        model.materials.emplace_back(mat);
    }
}

Mesh AssetManager::processMesh(aiMesh *mesh) {
    Mesh ret_mesh{};

    // 预留存内存 优化性能
    unsigned int const vertex_count = mesh->mNumVertices;
    ret_mesh.vertices.reserve(vertex_count);
    if (mesh->HasNormals()) { ret_mesh.normals.reserve(vertex_count); }
    if (mesh->mTextureCoords[0]) { ret_mesh.tex_coords.reserve(vertex_count); }
    if (mesh->HasTangentsAndBitangents()) {
        ret_mesh.tangents.reserve(vertex_count);
        ret_mesh.bitangents.reserve(vertex_count);
    }

    for (unsigned int i = 0; i < vertex_count; ++i) {
        ret_mesh.vertices.emplace_back(mesh->mVertices[i].x,
                                       mesh->mVertices[i].y,
                                       mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            ret_mesh.normals.emplace_back(mesh->mNormals[i].x,
                                          mesh->mNormals[i].y,
                                          mesh->mNormals[i].z);
        }

        if (mesh->mTextureCoords[0]) {
            ret_mesh.tex_coords.emplace_back(mesh->mTextureCoords[0][i].x,
                                             mesh->mTextureCoords[0][i].y);

            if (mesh->HasTangentsAndBitangents()) {
                ret_mesh.tangents.emplace_back(mesh->mTangents[i].x,
                                               mesh->mTangents[i].y,
                                               mesh->mTangents[i].z);
                ret_mesh.bitangents.emplace_back(mesh->mBitangents[i].x,
                                                 mesh->mBitangents[i].y,
                                                 mesh->mBitangents[i].z);
            }
        } else {
            ret_mesh.tex_coords.emplace_back(0.0f, 0.0f);
        }
    }

    unsigned int faces = 0;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        faces += face.mNumIndices;
        ret_mesh.indices.reserve(faces);
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            ret_mesh.indices.emplace_back(face.mIndices[j]);
        }
    }
    ret_mesh.material_id = mesh->mMaterialIndex;

    return ret_mesh;
}

Texture2DAsset *
AssetManager::processTexture(aiMaterial *material, aiTextureType type,
                             std::filesystem::path const &root_path,
                             std::filesystem::path const &directory_path) {
    unsigned int const cnt = material->GetTextureCount(type);
    for (unsigned int i = 0; i < cnt; ++i) {
        aiString path{};
        material->GetTexture(type, i, &path);
        if (auto tex = loadTexture(root_path, directory_path / path.C_Str(),
                                   textureTypeFromAssimpType(type));
            nullptr != tex) {
            return tex;
        }
    }
    return nullptr;
}

Model *AssetManager::loadModel(std::filesystem::path const &root_path,
                               const std::filesystem::path &relative_path) {
    auto full_path = fromRelativePath(root_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Model path is directory: {}", relative_path.string());
        return nullptr;
    }

    if (_models.count(relative_path.string())) {
        return &_models[relative_path.string()];
    }

    Model            ret_model{};
    Assimp::Importer importer{};
    aiScene const   *scene = importer.ReadFile(
            full_path.string(),
            // optimize indexing
            aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
                    // normal
                    aiProcess_GenSmoothNormals |
                    // opengl uv different
                    aiProcess_FlipUVs |
                    // tangent
                    aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        spdlog::error("Assimp error: {}", importer.GetErrorString());
        return nullptr;
    }
    ret_model.file_path = relative_path;

    processMaterial(scene, root_path, ret_model);
    processNode(scene->mRootNode, scene, ret_model);

    auto [model_ref, was_ins] =
            _models.insert({relative_path.string(), std::move(ret_model)});
    return &model_ref->second;
}

Texture2DAsset *
AssetManager::loadTexture(std::filesystem::path const &root_path,
                          const std::filesystem::path &relative_path,
                          TextureType                  type) {
    auto full_path = fromRelativePath(root_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Texture2DAsset path is directory");
        return nullptr;
    }

    if (_textures.count(relative_path.string())) {
        return &_textures[relative_path.string()];
    }

    auto [tex_ref, was_ins] = _textures.insert(
            {relative_path.string(),
             transferCPUTextureToGPU(root_path, relative_path, type)});
    return &tex_ref->second;
}

void AssetManager::loadModelAsync(
        std::filesystem::path const        &root_path,
        const std::filesystem::path        &relative_path,
        std::function<void(Model *)> const &callback) {}

void AssetManager::loadTextureAsync(
        std::filesystem::path const                 &root_path,
        const std::filesystem::path                 &relative_path,
        std::function<void(Texture2DAsset *)> const &callback) {}

void AssetManager::loadWorld(std::filesystem::path const &file_path) {
    taixuworld                    = std::make_unique<JsonWorld>();
    taixuworld->file_path         = "gameplay/taixuworld.json";
    taixuworld->project_file_path = file_path;
    taixuworld->deserialize();
}

void AssetManager::witeWorld(std::filesystem::path const &root_path) {
    _world = std::make_unique<JsonWorld>();
    JsonLevel l1;
    l1.level_name              = "level 1-1";
    std::filesystem::path pp1  = "gameplay\\level";
    std::filesystem::path temp = pp1 / (l1.level_name + ".json");
    //std::filesystem::path pp2 = asset_file_path.parent_path() / temp;
    l1.level_path              = temp.string();
    //l1.p.vec3 = glm::vec3(0,0,0);
    //l1.type = testEnumType::TYPE1;

    JsonLevel l2;
    l2.level_name = "level 1-2";
    temp          = pp1 / (l2.level_name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    l2.level_path = temp.string();

    JsonGO go1;
    go1.name    = "floor";
    pp1         = "gameplay\\GO";
    temp        = pp1 / (go1.name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go1.GO_path = temp.string();

    JsonGO go2;
    go2.name    = "planet";
    pp1         = "gameplay\\GO";
    temp        = pp1 / (go2.name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go2.GO_path = temp.string();

    JsonTransform trans1;
    trans1.position.vec3 = glm::vec3(0, 0, 0);
    trans1.rotation.vec3 = glm::vec3(0, 0, 0);
    trans1.scale.vec3    = glm::vec3(10, 1, 10);

    JsonMesh mesh1;
    mesh1.obj_path = "assets/model/cube.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh1.visiable = true;

    JsonRigidBody body1;
    body1.shapeType             = RigidBodyShapeType::BOX;
    body1.motionType            = MotionType::STATIC;
    body1.rigid_body_scale.vec3 = glm::vec3(1, 1, 1);

    JsonTransform trans2;
    trans2.position.vec3 = glm::vec3(0, 6, 0);
    trans2.rotation.vec3 = glm::vec3(0, 0, 0);
    trans2.scale.vec3    = glm::vec3(1, 1, 1);

    JsonMesh mesh2;
    mesh2.obj_path = "assets/model/planet.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh2.visiable = true;

    JsonRigidBody body2;
    body2.shapeType             = RigidBodyShapeType::SPHERE;
    body2.motionType            = MotionType::DYNAMIC;
    body2.rigid_body_scale.vec3 = glm::vec3(1, 1, 1);

    go1.TransformComponent = trans1;
    go1.MeshComponent      = mesh1;
    go1.RigidBodyComponent = body1;

    go2.TransformComponent = trans2;
    go2.MeshComponent      = mesh2;
    go2.RigidBodyComponent = body2;

    l1.json_game_objects.push_back(go1);
    l1.json_game_objects.push_back(go2);
    l2.json_game_objects.push_back(go1);

    _world->json_levels.push_back(l1);
    _world->json_levels.push_back(l2);
    _world->project_file_path = root_path;
    std::string world_path    = "gameplay\\taixuworld.json";
    _world->file_path         = world_path;
    _world->serialize();
}

}// namespace taixu
