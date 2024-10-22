/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "file_watcher.hpp"

#include <taixu/common/log/logger.hpp>
#include <taixu/engine/engine.hpp>
#include <taixu/platform/os/path_utils.hpp>

#include <imgui/icons/IconsLucide.h>

namespace taixu::editor {

static const std::unordered_set<std::string_view> IGNORE_TABLE{".git"sv, ".gitignore"sv};

void recursiveLoadFileTree(FileTreeNodeT& entry) {
    for (const auto full_path = g_engine.getOpenedProject()->raw.project_path / entry.data.filepath;
         auto&      directory_entry : std::filesystem::directory_iterator(full_path)) {
        const auto& path = directory_entry.path();

        if (IGNORE_TABLE.contains(path.filename().string())) {
            continue;
        }

        FileEntryType type{FileEntryType::FILE};
        if (directory_entry.is_directory()) {
            type = FileEntryType::DIRECTORY;
        }

        FileTreeNodeT node{path.filename().string(),
                           getRelativePath(g_engine.getOpenedProject()->raw.project_path, path),
                           type,
                           {},
                           {}};

        if (type == FileEntryType::DIRECTORY) {
            node.data.filename = fmt::format("{} {}", ICON_LC_FOLDER, node.data.filename);
            entry.directory_childrens.emplace_back(node);
        } else if (type == FileEntryType::FILE) {
            entry.file_childrens.emplace_back(node);
        }
    }
    for (auto&& child : entry.directory_childrens) {
        recursiveLoadFileTree(child);
    }
}

}// namespace taixu::editor
