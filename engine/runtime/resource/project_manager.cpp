//
// Created by xmmmmmovo on 2023/2/19.
//

#include "project_manager.hpp"

#include "platform/os/file_service.hpp"

namespace taixu {
using json = nlohmann::json;

Status ProjectManager::openProject(std::string_view const& path) {
    // If the project is not loaded, load it from the JSON file
    std::filesystem::path project_path = path;
    project_path /= "manifest.json";
    std::ifstream file(project_path.c_str());
    if (!file.is_open()) {
        std::cerr << "Failed to open project file " << path << "\n";
        return Status::NO_SUCH_FILE_FAILED;
    }

    nlohmann::json data;
    file >> data;

    // Parse the project data from the JSON file
    std::string                   name         = data["name"];
    std::vector<std::string_view> texturePaths = data["asset"]["textures"];
    std::vector<std::string_view> modelPaths   = data["asset"]["models"];

    // Create a new project object and add it to the vector of projects
    opened_project = std::make_shared<Project>(Project{
            name,
            texturePaths,
            modelPaths,
    });

    current_path = project_path.parent_path();

    return Status::OK;
}

Status ProjectManager::createProject(std::string const& path,
                                     std::string const& name) {
    if (opened_project) { opened_project = nullptr; }
    return Status::OK;
}

Status ProjectManager::saveAsProject(const std::string& path) {
    if (opened_project == nullptr) {
        spdlog::error("current have no project opening, error");
        return Status::NO_OPEN_PROJECT;
    }

    return Status::OK;
}

Status ProjectManager::saveProject() {
    if (opened_project == nullptr) {
        spdlog::error("current have no project opening, error");
        return Status::NO_OPEN_PROJECT;
    }

    return Status::OK;
}

}// namespace taixu