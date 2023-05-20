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

Bone AssetManager::generateBone(std::string name, int id,
                                const aiNodeAnim *channel) {
    Bone ret_bone{};
    ret_bone.m_Name = name;
    ret_bone.m_ID = id;

    ret_bone.m_NumPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < ret_bone.m_NumPositions; ++positionIndex) {

        aiVector3D  aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float       timeStamp  = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position  = glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z);
        data.timeStamp = timeStamp;
        ret_bone.m_Positions.push_back(data);
    }

    ret_bone.m_NumRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < ret_bone.m_NumRotations; ++rotationIndex) {

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
        spdlog::error("Model path is directory: {}", relative_path.generic_string());
        return nullptr;
    }

    if (_models.count(relative_path.generic_string())) {
        return &_models[relative_path.generic_string()];
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

    auto [model_ref, was_ins] =
            _models.insert({relative_path.generic_string(), std::move(ret_model)});
    
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

    if (_textures.count(relative_path.generic_string())) {
        return &_textures[relative_path.generic_string()];
    }

    auto [tex_ref, was_ins] = _textures.insert(
            {relative_path.generic_string(),
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

void AssetManager::writeWorld(std::filesystem::path const &root_path) {
    _world = std::make_unique<JsonWorld>();
    JsonLevel l1;
    l1.level_name              = "level 1-1";
    std::filesystem::path pp1  = "gameplay/level";
    std::filesystem::path temp = pp1 / (l1.level_name + ".json");
    //std::filesystem::path pp2 = asset_file_path.parent_path() / temp;
    l1.level_path              = temp.generic_string();
    //l1.p.vec3 = glm::vec3(0,0,0);
    //l1.type = testEnumType::TYPE1;
    spdlog::debug(temp.generic_string());

    JsonLevel l2;
    l2.level_name = "level 1-2";
    temp          = pp1 / (l2.level_name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    l2.level_path = temp.generic_string();

    JsonGO go1;
    go1.name    = "floor";
    pp1         = "gameplay/GO";
    temp        = pp1 / (go1.name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go1.GO_path = temp.generic_string();

    JsonGO go2;
    go2.name    = "planet";
    pp1         = "gameplay/GO";
    temp        = pp1 / (go2.name + ".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go2.GO_path = temp.generic_string();

    JsonTransform trans1;
    trans1.position.vec3 = glm::vec3(0, 0, 0);
    trans1.rotation.vec3 = glm::vec3(0, 0, 0);
    trans1.scale.vec3    = glm::vec3(20, 0.5, 20);

    JsonMesh mesh1;
    mesh1.obj_path = "assets/models/cube.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh1.visiable = true;

    JsonRigidBody body1;
    body1.shapeType             = RigidBodyShapeType::BOX;
    body1.motionType            = MotionType::STATIC;
    body1.rigid_body_scale.vec3 = glm::vec3(20, 0.5, 20);

    JsonTransform trans2;
    trans2.position.vec3 = glm::vec3(0, 6, 0);
    trans2.rotation.vec3 = glm::vec3(0, 0, 0);
    trans2.scale.vec3    = glm::vec3(1, 1, 1);

    JsonMesh mesh2;
    mesh2.obj_path = "assets/models/planet.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh2.visiable = false;

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

    JsonTransform trans3;
    trans3.position.vec3 = glm::vec3(15, 15, 15);
    trans3.rotation.vec3 = glm::vec3(0, 0, 0);
    trans3.scale.vec3    = glm::vec3(1, 1, 1);

    JsonLight light1;
    light1.light_color.vec3 = glm::vec3(1.0,1.0,1.0);
    light1.light_type = LightSourseType::POINT;
    light1.TransformComponent = trans3;
    light1.name    = "light1";
    pp1         = "gameplay/GO";
    temp        = pp1 / (light1.name + ".json");
    light1.light_path = temp.generic_string();

    JsonLight light2;
    light2.light_color.vec3 = glm::vec3(1.0,0.0,0.0);
    light2.light_type = LightSourseType::POINT;
    light2.TransformComponent = trans3;
    light2.name    = "light2";
    pp1         = "gameplay/GO";
    temp        = pp1 / (light2.name + ".json");
    light2.light_path = temp.generic_string();

    l1.json_lights.push_back(light1);
    l1.json_lights.push_back(light2);
    l2.json_lights.push_back(light1);

    _world->json_levels.push_back(l1);
    _world->json_levels.push_back(l2);
    _world->project_file_path = root_path;
    std::string world_path    = "gameplay/taixuworld.json";
    _world->file_path         = world_path;

    GlobalJson global;
    global.project_file_path = root_path;
    global.render_global_path = "gameplay/global/render.global.json";

    JsonTexture p;
    p.name = "mars";
    p.texture_path = "assets/textures/mars.png";

    JsonTexture con;
    con.name = "concrete";
    con.texture_path = "assets/textures/concreteTexture.png";

    global.json_textures.push_back(p);
    global.json_textures.push_back(con);

    _world->global_json = global;
    _world->serialize();
}

FBXData *AssetManager::loadFBX(std::filesystem::path const &root_path,
                               std::filesystem::path const &relative_path) {
    auto full_path = fromRelativePath(root_path, relative_path);

    if (std::filesystem::is_directory(full_path)) {
        spdlog::error("FBX path is directory: {}", relative_path.generic_string());
        return nullptr;
    }

    FBXData ret_fbx{};

    if (_fbx_files.count(relative_path.generic_string())) {
        return &_fbx_files[relative_path.generic_string()];
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

    if (_models.count(relative_path.generic_string())) {
        ret_fbx.model = &_models[relative_path.generic_string()];
    }
    else
    {

        Model            ret_model{};
        ret_model.file_path = relative_path;
        ret_fbx.file_path = relative_path;
        //processMaterial(scene, root_path, ret_model);
        processNode(scene->mRootNode, scene, ret_model,&ret_fbx);


        int a = 0;
        auto [model_ref, model_was_ins] =
            _models.insert({relative_path.generic_string(), std::move(ret_model)});
        ret_fbx.model = &model_ref->second;
    }

    //animation
    if(scene->HasAnimations())
    {
        auto animation = scene->mAnimations[0];
        ReadHierarchyData(ret_fbx.m_RootNode,scene->mRootNode);
        ret_fbx.m_Duration = animation->mDuration;
        ret_fbx.m_TicksPerSecond = animation->mTicksPerSecond;
        ReadMissingBones(animation, &ret_fbx);
    }
    
    auto [fbx_ref, fbx_was_ins] =
            _fbx_files.insert({relative_path.generic_string(), std::move(ret_fbx)});

    return &fbx_ref->second;
}


void AssetManager::processNode(aiNode *node, aiScene const *scene,
                               Model &model,FBXData *fbx) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.emplace_back(processSkinnedMesh(mesh,scene,fbx));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model,fbx);
    }
}

void setBoneData(glm::ivec4 &ids,glm::vec4 &weights, int boneID, float weight)
	{
		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
		{
			if (ids[i] < 0)
			{
				weights[i] = weight;
				ids[i] = boneID;
				break;
			}
		}
	}

void AssetManager::processWeights(std::vector<glm::ivec4> &bone_ids,
                                  std::vector<glm::vec4> &bone_weights,
                                  //const std::vector<std::uint32_t>&indices,
                                  aiMesh *mesh, const aiScene *scene, 
                                  std::map<string, BoneInfo> &boneInfoMap,
	                              int &boneCount) {

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
            int         boneID   = -1;
            std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
            if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
                BoneInfo newBoneInfo;
                newBoneInfo.id     = boneCount;
                newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
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
                setBoneData(bone_ids[vertexId],bone_weights[vertexId], boneID, weight);
            }
            //int a = 0;
    }

}

Mesh AssetManager::processSkinnedMesh(aiMesh *mesh, aiScene const *scene, FBXData *fbx) { 
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

        if(mesh->HasBones())
        {
            glm::ivec4 ids = glm::ivec4(-1,-1,-1,-1);
            glm::vec4 weights = glm::vec4(0,0,0,0);

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


void AssetManager::ReadMissingBones(const aiAnimation* animation, FBXData *fbx)
	{
		int size = animation->mNumChannels;
		//reading channels(bones engaged in an animation and their keyframes)
		for (int i = 0; i < size; i++)
		{
			auto channel = animation->mChannels[i];
			std::string boneName = channel->mNodeName.data;

			if (fbx->m_BoneInfoMap.find(boneName) == fbx->m_BoneInfoMap.end())
			{
				fbx->m_BoneInfoMap[boneName].id = fbx->m_BoneCounter;
				fbx->m_BoneCounter++;
			}
            fbx->skeleton.emplace_back(generateBone(channel->mNodeName.data,
				fbx->m_BoneInfoMap[channel->mNodeName.data].id, channel));
		}
	}

	void AssetManager::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
	{
		assert(src);

		dest.name = src->mName.data;
		dest.transformation = ConvertMatrixToGLMFormat(src->mTransformation);
		dest.childrenCount = src->mNumChildren;

		for (int i = 0; i < src->mNumChildren; i++)
		{
			AssimpNodeData newData;
			ReadHierarchyData(newData, src->mChildren[i]);
			dest.children.push_back(newData);
		}
	}
}// namespace taixu
