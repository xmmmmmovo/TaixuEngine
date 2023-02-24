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
#include <spdlog/spdlog.h>

#include"graphics/render/model.hpp"
#include"graphics/render/texture.hpp"


namespace taixu::resource {
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
    void loadAsset(std::string file_path) 
	{
        //TODO::adapte the structure of .json file
        
        //Json::Reader reader;
        //Json::Value  root;

        ////从字符串中读取数据
        //if (reader.parse(str, root)) {
        //    string name = root["name"].asString();
        //    int    age  = root["nomen"].asInt();
        //    string sex  = root["sex"].asString();
        //    cout << name + "," << age << "," << sex << endl;
        //}
        std::shared_ptr<Asset> new_asset = std::make_shared<Asset>();
        std::uint8_t           new_guid = GUID_Generator::generate_new_guid();
        new_asset->guid                  = new_guid;
        //new_asset.name = root["name"].asString();
        //new_asset.type=root["type"].asString();
        //new_asset.location = root["location"].asString();
        asset_list.push_back(new_asset);
	}
    
    void loadAsset(std::string file_path, AssetType asset_type);
	
};
}

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
