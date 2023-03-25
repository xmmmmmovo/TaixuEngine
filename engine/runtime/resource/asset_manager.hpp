//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <spdlog/spdlog.h>

#include <atomic>
#include <cstdint>
#include <fstream>
#include <limits>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>


namespace taixu {
constexpr std::uint8_t INVALID_GUID = std::numeric_limits<std::uint8_t>::max();
enum AssetType { MODEL, TEXTURE };
class GUID_Generator {
public:
    static std::uint8_t generate_new_guid();

private:
    static std::atomic<std::uint8_t> next_id;
};
struct Asset {
    std::uint8_t guid;
    std::string  name;
    std::string  type;
    std::string  location;
};
class AssetManager {
public:
    AssetManager() = default;
    std::vector<Asset> asset_list;
    using Json                  = nlohmann::json;
    std::string asset_file_path = "INVALID";

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Asset, name, type, location);


    void loadAsset(std::string file_path) {

        std::ifstream f(file_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        } else
            asset_file_path = file_path;
        Json data = Json::parse(f);
        
        for (auto i : data["assets"].items()) {
            Asset new_asset;
            std::uint8_t new_guid = GUID_Generator::generate_new_guid();
            new_asset.guid       = new_guid;
            Json j                = i.value();
            from_json(j, new_asset);
            asset_list.push_back(new_asset);
        }
    }
    void writeAsset();
    void loadAsset(std::string file_path, AssetType asset_type);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
