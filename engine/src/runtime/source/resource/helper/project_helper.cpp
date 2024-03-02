//
// Created by xmmmmmovo on 3/2/2024.
//

#include "project_helper.hpp"

#include "common/log/logger.hpp"
#include "resource/json/json_parser.hpp"
#include "resource/res_type/json_data/project.hpp"

namespace taixu {

std::shared_ptr<Project> openProject(std::filesystem::path const& path) {
    std::shared_ptr<Project> project = std::make_shared<Project>();

    static constexpr std::string_view MANIFEST_NAME = "manifest.json";

    const std::filesystem::path manifest_path = path / MANIFEST_NAME;
    project->project_path                     = path;
    if (std::optional<Manifest> const manifest =
                loadFromJsonFile<Manifest>(manifest_path);
        manifest.has_value()) {
        project->manifest = std::move(manifest.value());
    } else {
        return nullptr;
    }

    return project;
}

std::shared_ptr<Project> createProject(std::filesystem::path const& path,
                                       std::string const&           name,
                                       std::string const&           author,
                                       std::string const& description) {

    return nullptr;
}

bool saveProject() { return true; }

}// namespace taixu