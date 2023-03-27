//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <memory>
#include <vector>
#include <string>

#include "guid_genenrator.hpp"

namespace taixu {

struct Asset {
    std::uint8_t guid;
    std::string  name;
    std::string  type;
    std::string  location;
};
enum AssetType { MODEL, TEXTURE };
class AssetManager {
public:
    AssetManager() = default;
    std::vector<Asset> asset_list;
    using Json                  = nlohmann::json;
    std::filesystem::path asset_file_path = "INVALID";

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Asset, name, type, location);


    void loadAsset(std::filesystem::path const &file_path) {


        std::ifstream f(file_path.c_str());
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        } else
            asset_file_path = file_path.parent_path();

        Json data = Json::parse(f);
        
        for (auto i : data["assets"].items()) {
            Asset new_asset;
            std::uint8_t new_guid = GUID_Generator::generate_new_guid();
            new_asset.guid       = new_guid;
            Json j                = i.value();
            from_json(j, new_asset);
            asset_list.push_back(new_asset);
        }
        int a=0;
    }
    void writeAsset();
    void loadAsset(const std::string &file_path, const AssetType &asset_type);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
