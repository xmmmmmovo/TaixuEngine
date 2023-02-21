//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include <string>
#include <vector>

#include "interface/component.hpp"

namespace taixu::editor {
class FileComponent : public IUIComponent {
private:
    std::vector<std::string_view> file_tree;
    static ImGuiWindowFlags constexpr window_flags =
            ImGuiWindowFlags_HorizontalScrollbar;

public:
    void init() override {}
    void update() override {
        // Child 1: no border, enable horizontal scrollbar
        {
            ImGui::BeginChild(
                    "FileTree",
                    ImVec2(ImGui::GetWindowContentRegionWidth() * 0.2f, 0.f),
                    false, window_flags);
            for (int i = 0; i < 100; i++)
                ImGui::Text("%04d: scrollable region", i);
            ImGui::EndChild();
        }

        ImGui::SameLine();

        // Child 2: rounded border
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("FilePreview", ImVec2(0, 0), true);
            if (ImGui::BeginTable("split", 2,
                                  ImGuiTableFlags_Resizable |
                                          ImGuiTableFlags_NoSavedSettings)) {
                for (int i = 0; i < 100; i++) {
                    ImGui::TableNextColumn();
                    ImGui::Button("111", ImVec2(-FLT_MIN, 0.0f));
                }
                ImGui::EndTable();
            }
            ImGui::EndChild();
            ImGui::PopStyleVar();
        }
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_FILE_COMPONENT_HPP
