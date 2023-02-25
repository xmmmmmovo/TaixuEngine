//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <cstdint>
#include<string>
#include<memory>
#include<atomic>
#include<limits>
#include < fstream >
#include <spdlog/spdlog.h>
#include<nlohmann/json.hpp>
#include"graphics/render/model.hpp"
#include"graphics/render/texture.hpp"


namespace taixu {
constexpr std::uint8_t INVALID_GUID = std::numeric_limits<std::uint8_t>::max();
enum AssetType {Model,Texture};
class GUID_Generator 
{
public:
    static std::uint8_t       generate_new_guid();
private:
    static std::atomic<std::uint8_t> next_id;
};
struct Asset 
{
    std::uint8_t guid;
    std::string name;
    std::string type;
    std::string location;
};
class Asset_Manager 
{
public:
    Asset_Manager()=default;
    std::vector<std::shared_ptr<Asset>> asset_list;
    using Json=nlohmann::json;
    std::string asset_file_path = "INVALID";

    void from_json(const Json& j, std::shared_ptr<Asset> asset) {
        j.at("type").get_to(asset->type);
        j.at("name").get_to(asset->name);
        j.at("location").get_to(asset->location);
    }
    void to_json(Json& j, std::shared_ptr<Asset> asset) {
        j = Json{{"type", asset->type},
                 {"name", asset->name},
                 {"location", asset->location}};
    }
    
    void loadAsset(std::string file_path) 
	{
        std::ifstream f(file_path);
        if (!f.is_open()) 
        {
            spdlog::debug("Unable to load Asset configure file");
        } 
        else
            asset_file_path = file_path;
        Json data =Json::parse(f);


        ////从字符串中读取数据
        //if (reader.parse(str, root)) {
        //    string name = root["name"].asString();
        //    int    age  = root["nomen"].asInt();
        //    string sex  = root["sex"].asString();
        //    cout << name + "," << age << "," << sex << endl;
        //}
        for (auto i : data["assets"].items()) 
        {
            std::shared_ptr<Asset> new_asset = std::make_shared<Asset>();
            std::uint8_t new_guid = GUID_Generator::generate_new_guid();
            new_asset->guid       = new_guid;
            Json j          = i.value();
            from_json(j, new_asset);
            asset_list.push_back(new_asset);
        }
        //int a = 0;
	}
    void writeAsset();
    void loadAsset(std::string file_path, AssetType asset_type);
	
};
}

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
