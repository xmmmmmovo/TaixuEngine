//
// Created by xmmmmmovo on 2023/2/18.
//

#include <assimp/BaseImporter.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstddef>
#include <vector>

#include "asset_manager.hpp"
#include "assimp/material.h"
#include "raw_data/mesh.hpp"

namespace taixu {

void AssetManager::processNode(aiNode *node, const aiScene *scene,
                               Model &model) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh     = scene->mMeshes[node->mMeshes[i]];
        auto opt_mesh = processMesh(mesh, scene);
        if (opt_mesh.has_value()) {
            model.meshes.push_back(std::move(opt_mesh.value()));
        }
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model);
    }
}

std::optional<Mesh> AssetManager::processMesh(aiMesh        *mesh,
                                              const aiScene *scene) {
    std::vector<glm::vec3> vertices{};
    std::vector<glm::vec3> normals{};
    std::vector<glm::vec2> tex_coords{};

    std::vector<glm::vec3> tangents{};
    std::vector<glm::vec3> bitangents{};

    std::vector<unsigned int> indices{};

    // 预留存内存 优化性能
    unsigned int const vertex_count = mesh->mNumVertices;
    vertices.reserve(vertex_count);
    if (mesh->HasNormals()) { normals.reserve(vertex_count); }
    if (mesh->mTextureCoords[0]) { tex_coords.reserve(vertex_count); }
    if (mesh->HasTangentsAndBitangents()) {
        tangents.reserve(vertex_count);
        bitangents.reserve(vertex_count);
    }

    for (unsigned int i = 0; i < vertex_count; ++i) {
        vertices.emplace_back(mesh->mVertices[i].x, mesh->mVertices[i].y,
                              mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            normals.emplace_back(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                 mesh->mNormals[i].z);
        }

        if (mesh->mTextureCoords[0]) {
            tex_coords.emplace_back(mesh->mTextureCoords[0][i].x,
                                    mesh->mTextureCoords[0][i].y);

            if (mesh->HasTangentsAndBitangents()) {
                tangents.emplace_back(mesh->mTangents[i].x,
                                      mesh->mTangents[i].y,
                                      mesh->mTangents[i].z);
                bitangents.emplace_back(mesh->mBitangents[i].x,
                                        mesh->mBitangents[i].y,
                                        mesh->mBitangents[i].z);
            }
        } else {
            tex_coords.emplace_back(0.0f, 0.0f);
        }
    }

    unsigned int faces = 0;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        faces += face.mNumIndices;
        indices.reserve(faces);
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::optional<Texture *> diffuse_map{};

    return std::optional<Mesh>();
}

void AssetManager::processTexture(aiMaterial *material, aiTextureType type,
                                  const std::string &type_name, Model &model) {}

std::optional<Model>
AssetManager::loadModel(const std::filesystem::path &relative_path) {
    auto full_path = fromRelativePath(_asset_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Model path is directory");
        return std::nullopt;
    }

    if (_models.count(relative_path.string())) {
        return _models[relative_path.string()];
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
        return std::nullopt;
    }
    ret_model.file_path = relative_path;

    processNode(scene->mRootNode, scene, ret_model);

    _models[relative_path.string()] = ret_model;
    return ret_model;
}

std::optional<Texture>
AssetManager::loadTexture(const std::filesystem::path &relative_path) {
    auto full_path = fromRelativePath(_asset_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Texture path is directory");
        return std::nullopt;
    }
    Texture ret_texture;

    return ret_texture;
}

void AssetManager::loadModelAsync(
        const std::filesystem::path                     &relative_path,
        std::function<void(std::optional<Model>)> const &callback) {}

void AssetManager::loadTextureAsync(
        const std::filesystem::path                       &relative_path,
        std::function<void(std::optional<Texture>)> const &callback) {}

}// namespace taixu
