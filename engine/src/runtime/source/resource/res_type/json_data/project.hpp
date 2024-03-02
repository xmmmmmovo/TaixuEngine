//
// Created by xmmmmmovo on 2023/7/23.
//

#ifndef ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP
#define ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP

#include "manifest.hpp"
#include "world.hpp"

#include <filesystem>
#include <vector>

namespace taixu {

struct Project : std::enable_shared_from_this<Project> {
    std::filesystem::path project_path;
    Manifest              manifest{};
    std::vector<World>    worlds{};
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_RESOURCE_CONVERTED_DATA_PROJECT_HPP
