//
// Created by xmmmmmovo on 2023/2/18.
//

#include <assimp/material.h>
#include <assimp/scene.h>
#include <vector>

#include "asset_manager.hpp"
#include "helper/image_helper.hpp"
#include "raw_data/mesh.hpp"
#include "raw_data/texture.hpp"

namespace taixu {

void AssetManager::processNode(aiNode *node, const aiScene *scene,
                               Model &model) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.emplace_back(
                processMesh(mesh, scene, model.file_path.parent_path()));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model);
    }
}

Mesh AssetManager::processMesh(aiMesh *mesh, const aiScene *scene,
                               std::filesystem::path const &directory_path) {
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

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    ret_mesh.diffuse_map =
            processTexture(material, aiTextureType_DIFFUSE, directory_path);

    return ret_mesh;
}

Texture *
AssetManager::processTexture(aiMaterial *material, aiTextureType type,
                             std::filesystem::path const &directory_path) {
    unsigned int const cnt = material->GetTextureCount(type);
    for (unsigned int i = 0; i < cnt; ++i) {
        aiString path{};
        material->GetTexture(type, i, &path);
        if (auto tex = loadTexture(directory_path / path.C_Str(),
                                   textureTypeFromAssimpType(type));
            nullptr != tex) {
            return tex;
        }
    }
    return nullptr;
}

Model *AssetManager::loadModel(const std::filesystem::path &relative_path) {
    auto full_path = fromRelativePath(_asset_path, relative_path);

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

    processNode(scene->mRootNode, scene, ret_model);

    auto [iterator, was_inserted] =
            _models.insert({relative_path.string(), std::move(ret_model)});
    return &iterator->second;
}

Texture *AssetManager::loadTexture(const std::filesystem::path &relative_path,
                                   TextureType                  type) {
    auto full_path = fromRelativePath(_asset_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Texture path is directory");
        return nullptr;
    }

    if (_textures.count(relative_path.string())) {
        return &_textures[relative_path.string()];
    }

    int      width, height, channels;
    stbi_uc *data = load_image(full_path, &width, &height, &channels);
    if (!data) {
        spdlog::error("Load image error, path: {}", relative_path.string());
        return nullptr;
    }

    Texture ret_texture{};

    ret_texture.type      = type;
    ret_texture.file_path = relative_path;
    ret_texture.data      = data;

    auto [iterator, was_inserted] =
            _textures.insert({relative_path.string(), std::move(ret_texture)});
    return &iterator->second;
}

void AssetManager::loadModelAsync(
        const std::filesystem::path                     &relative_path,
        std::function<void(std::optional<Model>)> const &callback) {}

void AssetManager::loadTextureAsync(
        const std::filesystem::path                       &relative_path,
        std::function<void(std::optional<Texture>)> const &callback) {}

}// namespace taixu
