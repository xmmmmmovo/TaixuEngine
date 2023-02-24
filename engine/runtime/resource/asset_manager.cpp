//
// Created by xmmmmmovo on 2023/2/18.
//

#include "asset_manager.hpp"

namespace taixu::resource {
std::atomic<std::uint8_t> GUID_Generator::next_id{0};

std::uint8_t GUID_Generator::generate_new_guid() 
{
    std::atomic<std::uint8_t> new_id = next_id.load();
    next_id++;
    if (next_id >= INVALID_GUID) { spdlog::debug("GUID is overflow"); }
    return new_id;
}
void Asset_Manager::loadAsset(std::string file_path, AssetType asset_type) 
{
    std::shared_ptr<Asset> new_asset = std::make_shared<Asset>();
    new_asset->guid                  = GUID_Generator::generate_new_guid();
    new_asset->name     = file_path.substr(file_path.find_last_of('/') + 1);
    new_asset->location = file_path;
        
    if (asset_type == Model) 
        new_asset->type = "Model";
     else if (asset_type==Texture)
        new_asset->type = "Texture";

        asset_list.push_back(new_asset);
}
}// namespace taixu::resource
