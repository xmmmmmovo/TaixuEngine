//
// Created by xmmmmmovo on 2023/2/19.
//
#ifndef TAIXUENGINE_PROJECT_MANAGER_HPP
#define TAIXUENGINE_PROJECT_MANAGER_HPP

#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <vector>

#include "core/base/macro.hpp"

namespace taixu {

struct Project {
public:
    //name of project
    std::string_view name;
};

class ProjectManager {
private:
    // current project
    std::unique_ptr<Project> opened_project{nullptr};
    //file path of project
    std::filesystem::path    current_path;

public:
    ProjectManager() = default;

    Status openProject(std::string_view const &path);

    Status createProject(std::string const &path, std::string const &name);

    Status saveProject();

    Status saveAsProject(std::string const &path);

    [[nodiscard]] inline Project *getCurrentProject() const {
        return opened_project.get();
    }

    [[nodiscard]] inline std::filesystem::path getCurrentPath() const {
        return current_path;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_PROJECT_MANAGER_HPP