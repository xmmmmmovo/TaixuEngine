//
// Created by xmmmmmovo on 2023/2/19.
//

#include "project_manager.hpp"
//
namespace taixu {
//using json = nlohmann::json;
status ProjectManager::loadProjects() {
    // Open the project JSON file
    std::ifstream file("F:/Gproject/git/tests/project_data.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return status::NO_SUCH_FILE_FAILED;

    }

    // Read the entire file into a JSON object using nlohmann/json
    nlohmann::json data;
    try {
        file >> data;
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return status::PERMISSION_FAILED;
    }

    // Loop over the project objects and extract the data for each one
    // Extract the data from the JSON object and store it in C++ variables
    for (auto& project : data) {
        unsigned int             id           = project["id"];
        std::string              name         = project["name"];
        std::string              path         = project["path"];
        std::vector<std::string> texturesPath = project["asset"]["textures"];
        std::vector<std::string> modelsPath   = project["asset"]["models"];
        //Project                  newProject;
        auto                     ProjectPtr   = std::make_shared<Project>(name, path, texturesPath, modelsPath);
        projectData.push_back(ProjectPtr);
    }
     
    return status::OK;
}


status ProjectManager::openProject(std::string const& path) {
    // if one project is opening, close current project
    if (openingProject) { openingProject = nullptr; }
    // Check if the project is already loaded
    for (unsigned int i = 0; i < projectData.size();i++) {
        if (projectData[i]->path == path) {
            std::cout << "Project already loaded\n";
            openedPid = i;
            openingProject = projectData[i].get();
            return status::OK;
        }
    }

    // If the project is not loaded, load it from the JSON file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open project file " << path << "\n";
        return status::NO_SUCH_FILE_FAILED;
    }

    nlohmann::json data;
    file >> data;

    // Parse the project data from the JSON file
    std::string              name = data["name"];
    std::vector<std::string> texturePaths = data["asset"]["textures"];
    std::vector<std::string> modelPaths   = data["asset"]["models"];
  
    // Create a new project object and add it to the vector of projects
    auto newProject =
            std::make_shared<Project>(name, path, texturePaths, modelPaths);
    
    //the id would be the last index of the loaded project
    openedPid       = projectData.size();
    // set current opening project to read project 
    openingProject  = newProject.get();
    // save the project record in the local json
    //saveProjectLocal();
    // Return a pointer to the newly loaded project object
    return status::OK;
}

void ProjectManager::createProject(std::string const& path,
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


void ProjectManager::saveProjectLocal() { 
    // save the project that is not in the localist
    if (openingProject == nullptr) {
        std::cerr << "current have no project opening, error\n";
        return; 
    }
    //Project& proj = projectData[openedPid];
    std::ifstream file("F:/Gproject/git/tests/project_data.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open projects file\n";
        return;
    }

    std::cout << openingProject->name << std::endl;
    nlohmann::json data;
    file >> data;

    // Create a new project object
    int                      id           = openedPid;
    std::string              name         = openingProject->name;
    std::vector<std::string> texturePaths = openingProject->texturePath;
    std::vector<std::string> modelPaths   = openingProject->modelPath;


    nlohmann::json newProject = {
            {"id", id},
            {"name", name},
            {"asset", {{"textures", texturePaths}, {"models", modelPaths}}},
            {"path", openingProject->path}};

    // Add the new project to the "projects" array in the JSON file
    data["projects"].push_back(newProject);

    // Save the updated JSON data back to the file
    std::ofstream outfile("F:/Gproject/git/tests/project_data.json");
    outfile << std::setw(4) << data << std::endl;
}

void ProjectManager::saveProject(std::string const& path) { 
    if (openingProject == nullptr) {
        std::cout << "current have no project opening, error\n";
        return;
    }

    nlohmann::json saveFile;
    saveFile["name"]              = openingProject->name;
    saveFile["asset"]["textures"] = openingProject->texturePath;
    saveFile["asset"]["models"]   = openingProject->modelPath;

    // write the JSON object to a file
    std::string fileOutputPath = path; 
    std::cout << fileOutputPath << std::endl;
    std::ofstream outfile(fileOutputPath);
    outfile << std::setw(4) << saveFile << std::endl;

    //update the project information
    openingProject->path = path;

    //TODO: delete and replace the project object in the local list if it exist;
}
//
}// namespace taixu