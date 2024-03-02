//
// Created by xmmmmmovo on 3/2/2024.
//

#pragma once

namespace taixu {

struct Project;

std::shared_ptr<Project> openProject(std::filesystem::path const& path);

std::shared_ptr<Project> createProject(std::filesystem::path const& path,
                                       std::string const&           name,
                                       std::string const&           author,
                                       std::string const& description);

bool saveProject();

}// namespace taixu