//
// Created by xmmmmmovo on 3/2/2024.
//

#include "project_helper.hpp"

#include "taixu/common/log/logger.hpp"
#include "taixu/resource/json_data/manifest_json.hpp"

namespace taixu {

std::unique_ptr<Project> openProject(std::filesystem::path const& path) {
    static constexpr tx_string_view MANIFEST_NAME = "manifest.json";

    const std::filesystem::path manifest_path = path / MANIFEST_NAME;

    return nullptr;
}

std::unique_ptr<Project> createProject(std::filesystem::path const& path, tx_string const& name,
                                       tx_string const& author, tx_string const& description) {

    return nullptr;
}

bool saveProject() {
    return true;
}

}// namespace taixu
