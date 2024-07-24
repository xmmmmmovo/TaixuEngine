//
// Created by xmmmmmovo on 3/2/2024.
//

#include "project_helper.hpp"

#include "common/log/logger.hpp"
#include "resource/json/json_parser.hpp"
#include "resource/json_data/manifest_json.hpp"
#include "resource/json_data/project_json.hpp"

namespace taixu {

std::unique_ptr<Project> openProject(std::filesystem::path const& path) {
    std::unique_ptr<Project> project = std::make_unique<Project>();

    static constexpr std::string_view MANIFEST_NAME = "manifest.json";

    const std::filesystem::path manifest_path = path / MANIFEST_NAME;
    project->project_path                     = path;
    if (std::optional<Manifest> const manifest =
                loadFromJsonFile<Manifest>(manifest_path);
        manifest.has_value()) {
        project->manifest = manifest.value();
    } else {
        return nullptr;
    }

    return project;
}

std::unique_ptr<Project> createProject(std::filesystem::path const& path,
                                       std::string const&           name,
                                       std::string const&           author,
                                       std::string const& description) {

    return nullptr;
}

bool saveProject() { return true; }

}// namespace taixu