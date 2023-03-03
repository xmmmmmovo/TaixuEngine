//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>
#include <vector>

#include "hierarchy_component.hpp"
#include "interface/ui_component.hpp"

namespace taixu::editor {
class FileComponent : public IUIComponent {
private:
    std::vector<std::string_view> file_tree;
    static ImGuiWindowFlags constexpr window_flags =
            ImGuiWindowFlags_HorizontalScrollbar;

    std::filesystem::path root_path{"."};
    std::filesystem::path current_path{root_path};

    HierarchyComponent hierarchy_component{};

public:
    void update() override {
        {

            ImGui::BeginChild(
                    "FileTree",
                    ImVec2(ImGui::GetWindowContentRegionWidth() * 0.2f, 0.f),
                    false, window_flags);
            hierarchy_component.update();
            ImGui::EndChild();
        }
        // Child 1: no border, enable horizontal scrollbar

        ImGui::SameLine();
        // Child 2: rounded border
        {
            ImGui::BeginChild("ChildR", ImVec2(0, 260), false, window_flags);

            if (current_path != root_path) {
                if (ImGui::Button("<-")) {
                    current_path = current_path.parent_path();
                }
            }

            static float padding       = 16.0f;
            static float thumbnailSize = 128.0f;
            float        cellSize      = thumbnailSize + padding;

            float panelWidth  = ImGui::GetContentRegionAvail().x;
            int   columnCount = (int) (panelWidth / cellSize);
            if (columnCount < 1) columnCount = 1;

            if (ImGui::BeginTable("split", columnCount,
                                  ImGuiTableFlags_Resizable |
                                          ImGuiTableFlags_NoSavedSettings)) {
                for (auto& directoryEntry :
                     std::filesystem::directory_iterator(current_path)) {
                    const auto& path = directoryEntry.path();
                    auto        relativePath =
                            std::filesystem::relative(path, root_path);
                    std::string filenameString =
                            relativePath.filename().string();

                    ImGui::Button(filenameString.c_str(),
                                  {thumbnailSize, thumbnailSize});
                    if (ImGui::IsItemHovered() &&
                        ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                        if (directoryEntry.is_directory())
                            current_path /= path.filename();
                    }
                    ImGui::TextUnformatted(filenameString.c_str());
                    ImGui::TableNextColumn();
                }
                ImGui::EndTable();
            }

            ImGui::Columns(1);

            ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
            ImGui::SliderFloat("Padding", &padding, 0, 32);
            ImGui::EndChild();
        }
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_FILE_COMPONENT_HPP
