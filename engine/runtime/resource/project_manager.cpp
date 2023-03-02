//
// Created by xmmmmmovo on 2023/2/19.
//

#include "project_manager.hpp"

#include "platform/os/file_service.hpp"

namespace taixu {
using json = nlohmann::json;

Status ProjectManager::openProject(std::string_view const& path) {
    // If the project is not loaded, load it from the JSON file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open project file " << path << "\n";
        return Status::NO_SUCH_FILE_FAILED;
    }


    nlohmann::json data;
    file >> data;

    // Parse the project data from the JSON file
    std::string              name         = data["name"];
    std::vector<std::string> texturePaths = data["asset"]["textures"];
    std::vector<std::string> modelPaths   = data["asset"]["models"];

    // Create a new project object and add it to the vector of projects
    auto newProject =
            std::make_shared<Project>(name, path, texturePaths, modelPaths);

    //the id would be the last index of the loaded project
    openedPid      = projectData.size();
    // set current opening project to read project
    openingProject = newProject.get();
    // save the project record in the local json
    //saveProjectLocal();
    // Return a pointer to the newly loaded project object
    return Status::OK;
}

Status ProjectManager::createProject(std::string const& path,
                                     std::string const& name) {

    if (openingProject) { openingProject = nullptr; }
    //std::cout << path << std::endl;
    auto newProject = std::make_shared<Project>(
            name, path, std::vector<std::string>{}, std::vector<std::string>{});

    openingProject = newProject.get();
    auto sd        = getCurrentProject();
    saveProjectLocal();

    // Create a JSON object and fill it with data
    // Open the JSON file
}

Status ProjectManager::saveAsProject(const std::string& path) {}

Status ProjectManager::saveProject() {
    if (openingProject == nullptr) {
        spdlog::error("current have no project opening, error");
        return Status::NO_OPEN_PROJECT;
    }
}
}// namespace taixu