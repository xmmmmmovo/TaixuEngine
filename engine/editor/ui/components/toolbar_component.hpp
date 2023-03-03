//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_TOOLBAR_COMPONENT_HPP
#define TAIXUENGINE_TOOLBAR_COMPONENT_HPP

#include <IconsFontAwesome6.h>

#include "interface/ui_component.hpp"

namespace taixu::editor {

class ToolbarComponent : public IUIComponent {
public:
    void update() override {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        auto const& colors        = ImGui::GetStyle().Colors;
        const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                              ImVec4(buttonHovered.x, buttonHovered.y,
                                     buttonHovered.z, 0.5f));
        const auto& buttonActive = colors[ImGuiCol_ButtonActive];
        ImGui::PushStyleColor(
                ImGuiCol_ButtonActive,
                ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

        bool toolbarEnabled = (bool) true;

        ImVec4 tintColor = ImVec4(1, 1, 1, 1);
        if (!toolbarEnabled) tintColor.w = 0.5f;

        float size = ImGui::GetWindowHeight() - 4.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) -
                             (size * 0.5f));

        if (ImGui::Button(u8"中文！")) {}
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_PLAY "Play")) {}

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_TOOLBAR_COMPONENT_HPP
