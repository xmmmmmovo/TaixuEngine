//
// Created by xmmmmmovo on 2023/7/23.
//

#pragma once

#include "manifest_json.hpp"

#include <filesystem>
#include <vector>

namespace taixu {

struct Project {
    std::filesystem::path project_path;
    Manifest              manifest{};
};

}// namespace taixu
