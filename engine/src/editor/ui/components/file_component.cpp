/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "file_component.hpp"

#include <imgui/icons/IconsLucide.h>

#include <taixu/common/log/logger.hpp>
#include <taixu/engine/engine.hpp>

namespace taixu::editor {

static constexpr ImGuiWindowFlags   WINDOW_FLAGS = ImGuiWindowFlags_HorizontalScrollbar;
static constexpr ImGuiTreeNodeFlags PARENT_FLAGS = ImGuiTreeNodeFlags_SpanAvailWidth;
static constexpr ImGuiTreeNodeFlags LEAF_FLAGS =
        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

static std::string_view constexpr FILE_COMPONENT_NAME{"Files"};

static constexpr float PADDING        = 16.0f;
static constexpr float THUMBNAIL_SIZE = 128.0f;
static constexpr float CELL_SIZE      = THUMBNAIL_SIZE + PADDING;

void FileComponent::recursiveBuildFileTree(FileTreeNodeT& node) {
    ImGuiTreeNodeFlags flag = PARENT_FLAGS;
    if (node.directory_childrens.empty()) {
        flag = LEAF_FLAGS;
    }

    if (_view_model.selected_node == &node) {
        flag |= ImGuiTreeNodeFlags_Selected;
    }

    if (ImGui::TreeNodeEx(node.data.filename.c_str(), flag)) {
        if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
            _view_model.selected_node = &node;
        }

        for (auto&& child : node.directory_childrens) {
            recursiveBuildFileTree(child);
        }
        if (!(flag & ImGuiTreeNodeFlags_Leaf)) {
            ImGui::TreePop();
        }
    }
}

void FileComponent::buildFileTree() {
    recursiveBuildFileTree(_view_model.file_component_hierarchy);
}

void FileComponent::buildShowItems(std::vector<FileTreeNodeT>& nodes) const {
    for (auto& entry : nodes) {
        ImGui::PushID(entry.data.filename.data());
        ImGui::Button(entry.data.filename.data(), {THUMBNAIL_SIZE, THUMBNAIL_SIZE});

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (entry.data.filetype == FileEntryType::DIRECTORY) {
                _view_model.selected_node = &entry;
            } else {
            }
        }
        ImGui::TextUnformatted(entry.data.filename.data());

        ImGui::NextColumn();

        ImGui::PopID();
    }
}

void FileComponent::buildDirShowcase() const {
    float const panel_width  = ImGui::GetContentRegionAvail().x;
    int         column_count = static_cast<int>(panel_width / CELL_SIZE);
    if (column_count < 1) {
        column_count = 1;
    }

    ImGui::Columns(column_count, nullptr, false);

    buildShowItems(_view_model.selected_node->directory_childrens);
    buildShowItems(_view_model.selected_node->file_childrens);

    ImGui::Columns(1);
}

void FileComponent::update() {
    if (ImGui::Begin(FILE_COMPONENT_NAME.data(), nullptr, ImGuiWindowFlags_None)) {
        {
            if (ImGui::BeginChild("FileTree", ImVec2(ImGui::GetContentRegionAvail().x * 0.2f, 0.f), false,
                                  WINDOW_FLAGS)) {
                buildFileTree();
                ImGui::EndChild();
            }
        }

        ImGui::SameLine();
        {
            if (ImGui::BeginChild("DirShowCase", ImVec2(0, 0.f), false, WINDOW_FLAGS)) {
                buildDirShowcase();
                ImGui::EndChild();
            }
        }

        ImGui::End();
    }
}


}// namespace taixu::editor
