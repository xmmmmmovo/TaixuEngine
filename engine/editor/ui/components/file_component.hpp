//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include "interface/component.hpp"

namespace taixu::editor {
class FileComponent : public IUIComponent {
public:
    void init() override {}
    void update() override {
        // Child 1: no border, enable horizontal scrollbar
        {
            ImGuiWindowFlags window_flags =
                    ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild(
                    "ChildL",
                    ImVec2(ImGui::GetWindowContentRegionWidth() * 0.2f, 0),
                    false, window_flags);
            for (int i = 0; i < 100; i++)
                ImGui::Text("%04d: scrollable region", i);
            ImGui::EndChild();
        }

        ImGui::SameLine();

        // Child 2: rounded border
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ChildR", ImVec2(0, 0), true, window_flags);
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
