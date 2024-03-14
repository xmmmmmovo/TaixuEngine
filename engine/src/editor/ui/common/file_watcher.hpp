/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include "common/base/macro.hpp"
#include "hierarchy_struct.hpp"

namespace taixu::editor {

enum class EnumFileEntryType : uint8_t { FILE, DIRECTORY };

struct FileEntryModel {
    std::string           filename{};
    std::filesystem::path filepath{};
    EnumFileEntryType     filetype{};
};

template<typename DataT>
struct FileChildrensHierarchyDataNode : public HierarchyDataNode<DataT> {
    std::vector<FileChildrensHierarchyDataNode> file_childrens{};
    std::vector<FileChildrensHierarchyDataNode> directory_childrens{};
};

enum class EnumOpenFileType { SCENE };

using FileTreeNodeT = FileChildrensHierarchyDataNode<FileEntryModel>;

void recursiveLoadFileTree(FileTreeNodeT& entry);

EnumOpenFileType openFileTypeChecker(std::filesystem::path const& path);

}// namespace taixu::editor
