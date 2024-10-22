//
// Created by xmmmmmovo on 3/2/2024.
//

#pragma once

#include "common/hal/tx_string.hpp"

#include "taixu/management/project/project.hpp"

namespace taixu {

struct Project;

std::unique_ptr<Project> openProject(std::filesystem::path const& path);

std::unique_ptr<Project> createProject(std::filesystem::path const& path, tx_string const& name,
                                       tx_string const& author, tx_string const& description);

bool saveProject();

}// namespace taixu
