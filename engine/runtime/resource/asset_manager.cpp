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
void AssetManager::loadWorld(std::filesystem::path const &file_path) {}
void AssetManager::writeWorld() {
    _world = std::make_shared<jsonWorld>();
    LevelProperty l1;
    l1.level_name = "level 1-1";
    l1.level_path = "";
    l1.p.vec3 = glm::vec3(0,0,0);
    l1.type = testEnumType::TYPE1;
    _world->json_levels.push_back(l1);

    LevelProperty l2;
    l2.level_name = "level 1-2";
    l2.level_path = "";
    l2.p.vec3 = glm::vec3(0,0,0);
    l2.type = testEnumType::TYPE2;
    _world->json_levels.push_back(l2);
    std::string world_path = "taixuworld.json";
    _world->file_path = asset_file_path.parent_path() / world_path;
    _world->toJson();
}
}// namespace taixu
