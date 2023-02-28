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
    //id
    //unsigned int         id;
    //name of project
    std::string              name;
    //file path of project
    std::string              path;
    //texture list
    std::vector<std::string> texturePath;
    //model list
    std::vector<std::string> modelPath;
    Project() {}
    Project(std::string name, std::string path,
            std::vector<std::string> texturePath,
            std::vector<std::string> modelPath) {
        this->name        = name;
        this->path        = path;
        this->texturePath = std::move(texturePath);
        this->modelPath   = std::move(modelPath);
    }
};

class ProjectManager {
public:
    // current openingProject;

    // load project json file
    ProjectManager() {
        openingProject = nullptr;
        loadProjects();
    }
    status openProject(std::string const &path);
    void   createProject(std::string const &path, std::string const &name);
    void   deleteProject() { printf("delete"); };
    void   saveProject(std::string const &path);
    const std::vector<std::shared_ptr<Project>> &getLoadedProjects() const {
        return projectData;
    }

    void setOpeningProject(std::shared_ptr<Project> proj) {
        openingProject = proj.get();
    }
    Project *getCurrentProject() const { return openingProject; }
    //const Project getCurrentOpenedProject() { return projectData[openedPid]; }


private:
    //current opening project
    Project *openingProject;
    //TODO: Implement asset class in the future
    class assetManager;
    // object that store current opened obejct
    unsigned int                          openedPid;
    // vector store the current recorded project
    std::vector<std::shared_ptr<Project>> projectData;
    // record the project that has been loaded before
    void                                  saveProjectLocal();
    status                                loadProjects();
};

}// namespace taixu

#endif//TAIXUENGINE_PROJECT_MANAGER_HPP
