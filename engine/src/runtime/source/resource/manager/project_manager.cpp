//
// Created by xmmmmmovo on 2023/2/19.
//

#include "project_manager.hpp"

#include <filesystem>

#include <platform/os/file_service.hpp>
#include <common/log/logger.hpp>
#include <optional>
#include <resource/json/json_parser.hpp>
#include <string>

namespace taixu {

std::optional<Project> openProject(std::filesystem::path const& path) {
    // If the project is not loaded, load it from the JSON file
    std::filesystem::path manifest_path = path / "manifest.json";
    std::ifstream const   file((path / "manifest.json").generic_string());
    if (!file.is_open()) {
        ERROR_LOG("Failed to open project file {}", path.generic_string());
        return std::nullopt;
    }

    Project project;
    project.current_path = path;
    project.manifest     = loadFromJsonFile<Manifest>(manifest_path);
    return project;
}

std::optional<Project> createProject(std::filesystem::path const& path,
                                     std::string const&           name,
                                     std::string const&           author,
                                     std::string const&           description) {
    Project project;
    project.current_path  = path;
    project.manifest      = Manifest();
    project.manifest.name = name;
    project.manifest.author =
            author.empty() ? "noname" : author;// TODO: get current user name
    project.manifest.description = description;
    project.manifest.version     = "0.0.1";

    return project;
}

EnumStatus saveAsProject(const std::filesystem::path& path) { return EnumStatus::OK; }

EnumStatus saveProject() { return EnumStatus::OK; }

}// namespace taixu