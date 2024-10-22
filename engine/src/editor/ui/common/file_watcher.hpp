/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <filesystem>

#include "hierarchy_struct.hpp"

namespace taixu::editor {

enum class FileEntryType : uint8_t { FILE, DIRECTORY };

struct FileEntryModel {
    std::string           filename{};
    std::filesystem::path filepath{};
    FileEntryType         filetype{};
};

template<typename DataT>
struct FileChildrensHierarchyDataNode : public HierarchyDataNode<DataT> {
    std::vector<FileChildrensHierarchyDataNode> file_childrens{};
    std::vector<FileChildrensHierarchyDataNode> directory_childrens{};
};

enum class OpenFileType : uint8_t { SCENE };

using FileTreeNodeT = FileChildrensHierarchyDataNode<FileEntryModel>;

void recursiveLoadFileTree(FileTreeNodeT& entry);

OpenFileType openFileTypeChecker(std::filesystem::path const& path);

}// namespace taixu::editor
