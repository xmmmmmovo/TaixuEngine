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
}// namespace taixu::resource
