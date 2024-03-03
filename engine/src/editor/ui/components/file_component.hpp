//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include <filesystem>
#include <string>
#include <vector>

#include "platform/os/path.hpp"
#include "ui/common/ui_component.hpp"
#include "ui/common/view_model.hpp"

namespace taixu::editor {

class FileComponent : public AbstractUIComponent {
private:
    static ImGuiWindowFlags constexpr window_flags =
            ImGuiWindowFlags_HorizontalScrollbar;
    ImGuiTreeNodeFlags const parent_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
    ImGuiTreeNodeFlags const leaf_flags   = ImGuiTreeNodeFlags_SpanAvailWidth |
                                          ImGuiTreeNodeFlags_Leaf |
                                          ImGuiTreeNodeFlags_NoTreePushOnOpen;

    static std::string_view constexpr FILE_COMPONENT_NAME{"Files"};

private:
    void expandTreeNode(HierarchyNode<std::filesystem::path>& entry) {
        auto full_path = _view_model->project_path / entry.data;
        for (auto& directory_entry :
             std::filesystem::directory_iterator(full_path)) {
            const auto& path = directory_entry.path();
            if (path.filename() == ".git" || path.filename() == ".gitignore") {
                continue;
            }
            if (directory_entry.is_directory()) {
                entry.children.push_back(
                        {.name     = path.filename().generic_string(),
                         .data     = getRelativePath(_view_model->project_path,
                                                     path),
                         .children = {}});
            }
        }
    }

    void buildUpTreeNode(HierarchyNode<std::filesystem::path>& node) {
        if (node.expanded) {
            for (auto& child : node.children) {
                auto flag = parent_flags;
                if (_view_model->selected_node == &child) {
                    flag |= ImGuiTreeNodeFlags_Selected;
                }
                if (ImGui::TreeNodeEx(child.name.c_str(), parent_flags)) {
                    if (ImGui::IsMouseDoubleClicked(0) &&
                        ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
                        if (!child.expanded) { expandTreeNode(child); }
                        child.expanded = !child.expanded;
                        INFO_LOG("Double Clicked on: {}", child.name);
                        _view_model->selected_path = child.data;
                        _view_model->selected_node = &child;
                    }
                    buildUpTreeNode(child);
                    ImGui::TreePop();
                }
            }
        } else {
            return;
        }
    }

public:
    explicit FileComponent(ViewModel* view_model)
        : AbstractUIComponent(view_model) {}

    void update() {
        {
            ImGui::BeginChild(
                    "FileTree",
                    ImVec2(ImGui::GetContentRegionAvail().x * 0.2f, 0.f), false,
                    window_flags);

            for (auto& parent_entry : _view_model->path_hierarchy) {
                auto flag = parent_flags;
                if (_view_model->selected_node == &parent_entry) {
                    flag |= ImGuiTreeNodeFlags_Selected;
                }
                if (ImGui::TreeNodeEx(parent_entry.name.c_str(), flag)) {
                    if (ImGui::IsMouseDoubleClicked(0) &&
                        ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
                        if (!parent_entry.expanded) {
                            expandTreeNode(parent_entry);
                        }
                        parent_entry.expanded      = !parent_entry.expanded;
                        _view_model->selected_path = parent_entry.data;
                        _view_model->selected_node = &parent_entry;
                    }
                    if (parent_entry.expanded) {
                        buildUpTreeNode(parent_entry);
                    }
                    ImGui::TreePop();
                }
            }

            ImGui::EndChild();
        }

        ImGui::SameLine();
        {
            ImGui::BeginChild("ChildR", ImVec2(0, 0.f), false, window_flags);

            if (_view_model->selected_path != "") {
                if (ImGui::Button("<-")) {
                    _view_model->selected_path =
                            _view_model->selected_path.parent_path();
                }
            }

            static float padding        = 16.0f;
            static float thumbnail_size = 128.0f;
            float const  cell_size      = thumbnail_size + padding;

            float const panel_width = ImGui::GetContentRegionAvail().x;
            int column_count        = static_cast<int>(panel_width / cell_size);
            if (column_count < 1) { column_count = 1; }

            ImGui::Columns(column_count, 0, false);

            auto full_path =
                    _view_model->project_path / _view_model->selected_path;
            for (auto& directory_entry :
                 std::filesystem::directory_iterator(full_path)) {
                const auto&       path = directory_entry.path();
                std::string const filename_string =
                        path.filename().generic_string();


                ImGui::PushID(filename_string.c_str());
                ImGui::Button(filename_string.c_str(),
                              {thumbnail_size, thumbnail_size});

                if (ImGui::IsItemHovered() &&
                    ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                    if (directory_entry.is_directory()) {
                        _view_model->selected_path /= path.filename();
                    } else {
                    }
                }
                ImGui::TextUnformatted(filename_string.c_str());

                ImGui::NextColumn();

                ImGui::PopID();
            }

            ImGui::Columns(1);

            ImGui::SliderFloat("Thumbnail Size", &thumbnail_size, 16, 512);
            ImGui::SliderFloat("Padding", &padding, 0, 32);
            ImGui::EndChild();
        }
    }
};
}// namespace taixu::editor

#endif// TAIXUENGINE_FILE_COMPONENT_HPP
