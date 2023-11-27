//
// Created by xmmmmmovo on 2023/7/23.
//

#ifndef ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP
#define ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP

#include "resource/json/manifest_json.hpp"
#include "world.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace taixu {

struct Project {
    std::filesystem::path current_path;
    Manifest              manifest;
    std::vector<World>    worlds;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP
