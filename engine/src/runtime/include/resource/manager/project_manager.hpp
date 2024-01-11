//
// Created by xmmmmmovo on 2023/2/19.
//
#ifndef TAIXUENGINE_PROJECT_MANAGER_HPP
#define TAIXUENGINE_PROJECT_MANAGER_HPP

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <simdjson.h>

#include <common/base/core.hpp>
#include <common/base/macro.hpp>
#include <resource/res_type/json_data/project.hpp>

namespace taixu {

std::optional<Project> openProject(std::filesystem::path const& path);

std::optional<Project> createProject(std::filesystem::path const& path,
                                     std::string const&           name,
                                     std::string const&           author,
                                     std::string const&           description);

Status saveProject();

Status saveAsProject(std::filesystem::path const& path);


}// namespace taixu

#endif// TAIXUENGINE_PROJECT_MANAGER_HPP
