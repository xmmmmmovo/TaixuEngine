//
// Created by xmmmmmovo on 2023/2/19.
//
#ifndef TAIXUENGINE_PROJECT_MANAGER_HPP
#define TAIXUENGINE_PROJECT_MANAGER_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "core/base/macro.hpp"
#include "graphics/render/mesh.hpp"
#include "graphics/render/model.hpp"

namespace taixu {

class Project {
public:
    //name of project
    std::string_view              name;
    //file path of project
    std::string_view              path;
    //texture list
    std::vector<std::string_view> texture_path;
    //model list
    std::vector<std::string_view> model_path;
};

class ProjectManager {
private:
    // current project
    std::shared_ptr<Project> openingProject{nullptr};

public:
    ProjectManager() = default;

    Status openProject(std::string_view const &path);

    Status createProject(std::string const &path, std::string const &name);

    Status saveProject();

    Status saveAsProject(std::string const &path);

    [[nodiscard]] std::shared_ptr<Project> getProject() const {
        return openingProject;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_PROJECT_MANAGER_HPP
