//
// Created by xmmmmmovo on 2023/2/18.
//

#include "asset_manager.hpp"

namespace taixu {

void AssetManager::writeAsset() {
    if (asset_file_path != "INVALID")
    {
        std::ofstream o(asset_file_path);
        Json write;
        for (auto count : asset_list) 
        {   
            Json j;
            //to_json(j, count);
            to_json(j, count);
            write+=j;
        }
        Json assets{{"assets", write}};
        o << std::setw(4) << assets;
        o.close();
    }
}

void AssetManager::loadAsset(const std::string &file_path, const AssetType &asset_type) {
    Asset new_asset;
    new_asset.guid                  = GUID_Generator::generate_new_guid();
    new_asset.name     = file_path.substr(file_path.find_last_of('/') + 1);
    new_asset.location = file_path;
        
    if (asset_type == MODEL) 
        new_asset.type = "Model";
     else if (asset_type==TEXTURE)
        new_asset.type = "Texture";

        asset_list.push_back(new_asset);
}
void AssetManager::loadWorld(std::filesystem::path const &file_path) {
    auto taixuworld = std::make_shared<JsonWorld>();
    taixuworld->file_path = file_path.parent_path()/"taixuworld.json";
    taixuworld->asset_file_path = asset_file_path;
    taixuworld->deserialize();
}
void AssetManager::writeWorld() {
    _world = std::make_shared<JsonWorld>();
    JsonLevel l1;
    l1.level_name = "level 1-1";
    std::filesystem::path pp1 = "level";
    std::filesystem::path temp = pp1 / (l1.level_name+".json");
    //std::filesystem::path pp2 = asset_file_path.parent_path() / temp;
    l1.level_path = temp.string();
    //l1.p.vec3 = glm::vec3(0,0,0);
    //l1.type = testEnumType::TYPE1;

    JsonLevel l2;
    l2.level_name = "level 1-2";
    temp = pp1 / (l2.level_name+".json");
    //pp2 = asset_file_path.parent_path() / temp;
    l2.level_path = temp.string();

    JsonGO go1;
    go1.name = "floor";
    pp1 = "GO";
    temp = pp1 / (go1.name+".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go1.GO_path = temp.string();

    JsonGO go2;
    go2.name = "planet";
    pp1 = "GO";
    temp = pp1 / (go2.name+".json");
    //pp2 = asset_file_path.parent_path() / temp;
    go2.GO_path = temp.string();

    JsonTransform trans1;
    trans1.position.vec3 = glm::vec3(0,0,0);
    trans1.rotation.vec3 = glm::vec3(0,0,0);
    trans1.scale.vec3 = glm::vec3(10,1,10);

    JsonMesh mesh1;
    mesh1.obj_path = "assets/model/cube.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh1.visiable = true;

    JsonRigidBody body1;
    body1.shapeType = RigidBodyShapeType::BOX;
    body1.motionType = MotionType::STATIC;
    body1.rigid_body_scale.vec3 = glm::vec3(1,1,1);

    JsonTransform trans2;
    trans2.position.vec3 = glm::vec3(0,6,0);
    trans2.rotation.vec3 = glm::vec3(0,0,0);
    trans2.scale.vec3 = glm::vec3(1,1,1);

    JsonMesh mesh2;
    mesh2.obj_path = "assets/model/planet.obj";
    //mesh1.material_path = "assets/textures/concreteTexture.png";
    mesh2.visiable = true;

    JsonRigidBody body2;
    body2.shapeType = RigidBodyShapeType::SPHERE;
    body2.motionType = MotionType::DYNAMIC;
    body2.rigid_body_scale.vec3 = glm::vec3(1,1,1);

    go1.TransformComponent = trans1;
    go1.MeshComponent = mesh1;
    go1.RigidBodyComponent = body1;

    go2.TransformComponent = trans2;
    go2.MeshComponent = mesh2;
    go2.RigidBodyComponent = body2;

    l1.json_game_objects.push_back(go1);
    l1.json_game_objects.push_back(go2);
    l2.json_game_objects.push_back(go1);

    //l2.p.vec3 = glm::vec3(0,0,0);
    //l2.type = testEnumType::TYPE2;
    _world->json_levels.push_back(l1);
    _world->json_levels.push_back(l2);
    _world->asset_file_path = asset_file_path;
    std::string world_path = "taixuworld.json";
    _world->file_path = world_path;
    _world->serialize();
}
}// namespace taixu
