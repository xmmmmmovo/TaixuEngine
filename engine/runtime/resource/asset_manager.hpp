//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_RESOURCE_MANAGER_HPP
#define TAIXUENGINE_RESOURCE_MANAGER_HPP

#include <filesystem>
#include <spdlog/spdlog.h>

#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "management/ecs/guid_genenrator.hpp"
#include "platform/os/path.hpp"

namespace taixu {

struct BaseAsset {
    std::string name{};
    std::string location{};
};

class TextureAsset : public BaseAsset {};

class AssetManager {
    //    PROTOTYPE_ONLY_GETTER(std::unordered_map<std::filesystem::path>);

public:
    using Json = nlohmann::json;

    void loadAsset(std::filesystem::path const &file_path) { return; }
};
}// namespace taixu

#endif//TAIXUENGINE_RESOURCE_MANAGER_HPP
