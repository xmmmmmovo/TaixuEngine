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
#include <unordered_map>
#include <vector>

#include "guid_genenrator.hpp"
#include "platform/os/path.hpp"

namespace taixu {

enum class AssetType { UNDEFINED, MODEL, TEXTURE };

template<typename Data>
struct Asset {
    std::string name{};
    AssetType   type{AssetType::UNDEFINED};
    std::string location{};
    Data        data{};
};


class AssetManager {
    //    PROTOTYPE_ONLY_GETTER(std::unordered_map<>)

public:
    using Json = nlohmann::json;

    void loadAsset(std::filesystem::path const &file_path) { return; }

    void loadAsset(const std::string &file_path, const AssetType &asset_type);
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
