//
// Created by xmmmmmovo on 2023/2/18.
//

#include "assimp/material.h"
#include "assimp/scene.h"
#include <vector>

#include "asset_manager.hpp"
#include "resource/helper/image_helper.hpp"
#include "resource/json/json_type/world_json.hpp"
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

Bone AssetManager::generateBone(std::string name, int id,
                                const aiNodeAnim *channel) {
    Bone ret_bone{};
    ret_bone.m_Name = name;
    ret_bone.m_ID   = id;

    ret_bone.m_NumPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < ret_bone.m_NumPositions;
         ++positionIndex) {

        aiVector3D  aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float       timeStamp  = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position  = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);
        data.timeStamp = timeStamp;
        ret_bone.m_Positions.push_back(data);
    }

    ret_bone.m_NumRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < ret_bone.m_NumRotations;
         ++rotationIndex) {

        aiQuaternion aiOrientation =
                channel->mRotationKeys[rotationIndex].mValue;
        float       timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = glm::quat(aiOrientation.w, aiOrientation.x,
                                     aiOrientation.y, aiOrientation.z);
        data.timeStamp   = timeStamp;
        ret_bone.m_Rotations.push_back(data);
    }

    ret_bone.m_NumScalings = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < ret_bone.m_NumScalings; ++keyIndex) {

        aiVector3D scale     = channel->mScalingKeys[keyIndex].mValue;
        float      timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale   data;
        data.scale     = glm::vec3(scale.x, scale.y, scale.z);
        data.timeStamp = timeStamp;
        ret_bone.m_Scales.push_back(data);
    }

    return ret_bone;
}

Model *AssetManager::loadModel(std::filesystem::path const &root_path,
                               const std::filesystem::path &relative_path) {
    auto full_path = fromRelativePath(root_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("Model path is directory: {}",
                      relative_path.generic_string());
        return nullptr;
    }

    if (_models.count(full_path.generic_string().c_str())) {
        return &_models[full_path.generic_string().c_str()];
    }

    Model            ret_model{};
    Assimp::Importer importer{};
    aiScene const   *scene = importer.ReadFile(
            full_path.generic_string(),
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

    auto [model_ref, was_ins] = _models.insert(
            {full_path.generic_string().c_str(), std::move(ret_model)});


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

    if (_textures.count(full_path.generic_string().c_str())) {
        return &_textures[full_path.generic_string().c_str()];
    }

    auto [tex_ref, was_ins] = _textures.insert(
            {full_path.generic_string().c_str(),
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

JsonWorld *AssetManager::loadWorld(std::filesystem::path const &file_path) {
    _taixu_world                    = std::make_unique<JsonWorld>();
    _taixu_world->file_path         = "gameplay/taixuworld.json";
    _taixu_world->project_file_path = file_path;
    spdlog::info("load world: {}", _taixu_world->file_path.generic_string());
    _taixu_world->deserialize();
    return _taixu_world.get();
}

FBXData *AssetManager::loadFBX(std::filesystem::path const &root_path,
                               std::filesystem::path const &relative_path) {
    auto full_path = fromRelativePath(root_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("FBX path is directory: {}",
                      relative_path.generic_string());
        return nullptr;
    }

    FBXData ret_fbx{};

    if (_fbx_files.count(full_path.generic_string().c_str())) {
        return &_fbx_files[full_path.generic_string().c_str()];
    }

    Assimp::Importer importer{};
    aiScene const   *scene = importer.ReadFile(
            full_path.generic_string(),
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

    if (_models.count(full_path.generic_string().c_str())) {
        ret_fbx.model = &_models[full_path.generic_string().c_str()];
    } else {

        Model ret_model{};
        ret_model.file_path = relative_path;
        ret_fbx.file_path   = relative_path;
        //processMaterial(scene, root_path, ret_model);
        processNode(scene->mRootNode, scene, ret_model, &ret_fbx);

        auto [model_ref, model_was_ins] = _models.insert(
                {full_path.generic_string().c_str(), std::move(ret_model)});
        ret_fbx.model = &model_ref->second;
    }

    //animation
    if (scene->HasAnimations()) {
        auto animation = scene->mAnimations[0];
        ReadHierarchyData(ret_fbx.m_RootNode, scene->mRootNode);
        ret_fbx.m_Duration       = animation->mDuration;
        ret_fbx.m_TicksPerSecond = animation->mTicksPerSecond;
        ReadMissingBones(animation, &ret_fbx);
    }

    auto [fbx_ref, fbx_was_ins] = _fbx_files.insert(
            {full_path.generic_string().c_str(), std::move(ret_fbx)});

    return &fbx_ref->second;
}


void AssetManager::processNode(aiNode *node, aiScene const *scene, Model &model,
                               FBXData *fbx) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.emplace_back(processSkinnedMesh(mesh, scene, fbx));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model, fbx);
    }
}

void setBoneData(glm::ivec4 &ids, glm::vec4 &weights, int boneID,
                 float weight) {
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
        if (ids[i] < 0) {
            weights[i] = weight;
            ids[i]     = boneID;
            break;
        }
    }
}

void AssetManager::processWeights(std::vector<glm::ivec4> &bone_ids,
                                  std::vector<glm::vec4>  &bone_weights,
                                  //const std::vector<std::uint32_t>&indices,
                                  aiMesh *mesh, const aiScene *scene,
                                  std::map<string, BoneInfo> &boneInfoMap,
                                  int                        &boneCount) {

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
        int         boneID   = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            BoneInfo newBoneInfo;
            newBoneInfo.id     = boneCount;
            newBoneInfo.offset = convertMatrixToGlmFormat(
                    mesh->mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID                = boneCount;
            boneCount++;
        } else {
            boneID = boneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights    = mesh->mBones[boneIndex]->mWeights;
        int  numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
            int   vertexId = weights[weightIndex].mVertexId;
            float weight   = weights[weightIndex].mWeight;
            assert(vertexId <= bone_ids.size());
            setBoneData(bone_ids[vertexId], bone_weights[vertexId], boneID,
                        weight);
        }
        //int a = 0;
    }
}

Mesh AssetManager::processSkinnedMesh(aiMesh *mesh, aiScene const *scene,
                                      FBXData *fbx) {
    Mesh ret_mesh{};

    // 预留存内存 优化性能
    unsigned int const vertex_count = mesh->mNumVertices;
    ret_mesh.vertices.reserve(vertex_count);
    std::vector<VertexRelateBoneInfo> related_bones_Info;
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

        if (mesh->HasBones()) {
            glm::ivec4 ids     = glm::ivec4(-1, -1, -1, -1);
            glm::vec4  weights = glm::vec4(0, 0, 0, 0);

            ret_mesh.related_bones_id.push_back(ids);
            ret_mesh.related_bones_weights.push_back(weights);
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

    processWeights(ret_mesh.related_bones_id, ret_mesh.related_bones_weights,
                   //ret_mesh.indices,
                   mesh, scene, fbx->m_BoneInfoMap, fbx->m_BoneCounter);

    return ret_mesh;
}


void AssetManager::ReadMissingBones(const aiAnimation *animation,
                                    FBXData           *fbx) {
    int size = animation->mNumChannels;
    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++) {
        auto        channel  = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (fbx->m_BoneInfoMap.find(boneName) == fbx->m_BoneInfoMap.end()) {
            fbx->m_BoneInfoMap[boneName].id = fbx->m_BoneCounter;
            fbx->m_BoneCounter++;
        }
        fbx->skeleton.emplace_back(generateBone(
                channel->mNodeName.data,
                fbx->m_BoneInfoMap[channel->mNodeName.data].id, channel));
    }
}

void AssetManager::ReadHierarchyData(AssimpNodeData &dest, const aiNode *src) {
    assert(src);

    dest.name           = src->mName.data;
    dest.transformation = convertMatrixToGlmFormat(src->mTransformation);
    dest.childrenCount  = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++) {
        AssimpNodeData newData;
        ReadHierarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}
}// namespace taixu
