/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "file_watcher.hpp"

#include "common/log/logger.hpp"
#include "engine/engine.hpp"
#include "platform/os/path.hpp"

#include <imgui/icons/IconsLucide.h>


namespace taixu::editor {

static std::unordered_set IGNORE_TABLE{".git"sv, ".gitignore"sv};

void recursiveLoadFileTree(FileTreeNodeT& entry) {
    for (const auto full_path = g_engine.getOpenedProject()->project_path /
                                entry.data.filepath;
         auto& directory_entry :
         std::filesystem::directory_iterator(full_path)) {
        const auto& path = directory_entry.path();

        if (IGNORE_TABLE.contains(path.filename().string())) { continue; }

        EnumFileEntryType type{EnumFileEntryType::FILE};
        if (directory_entry.is_directory()) {
            type = EnumFileEntryType::DIRECTORY;
        }

        FileTreeNodeT node{
                path.filename().string(),
                getRelativePath(g_engine.getOpenedProject()->project_path,
                                path),
                type,
                {},
                {}};

        if (type == EnumFileEntryType::DIRECTORY) {
            node.data.filename =
                    fmt::format("{} {}", ICON_LC_FOLDER, node.data.filename);
            entry.directory_childrens.emplace_back(node);
        } else if (type == EnumFileEntryType::FILE) {
            entry.file_childrens.emplace_back(node);
        }
    }
    for (auto&& child : entry.directory_childrens) {
        recursiveLoadFileTree(child);
    }
}

}// namespace taixu::editor