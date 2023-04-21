//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <spdlog/spdlog.h>

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "guid_genenrator.hpp"
#include "platform/os/path.hpp"

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
    using Json                            = nlohmann::json;
    std::filesystem::path asset_file_path = "INVALID";

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Asset, name, type, location);


    void loadAsset(std::filesystem::path const &file_path) {
        

        std::ifstream f(file_path.c_str());
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        } else {
            asset_file_path = file_path.parent_path();
        }

        auto dir_path = asset_file_path.parent_path();

        Json data = Json::parse(f);

        for (auto &i : data["assets"].items()) {
            Asset              new_asset;
            std::uint8_t const new_guid = GuidGenerator::generateNewGuid();
            new_asset.guid              = new_guid;
            Json const j                = i.value();
            from_json(j, new_asset);
            std::filesystem::path temppath =   dir_path / new_asset.location;
            new_asset.location = temppath.string();
            asset_list.push_back(new_asset);
        }
    }
    void writeAsset();
    void loadAsset(const std::string &file_path, const AssetType &asset_type);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
