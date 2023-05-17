//
// Created by xmmmmmovo on 2023/3/25.
//

#ifndef TAIXUENGINE_STATUSBAR_COMPONENT_HPP
#define TAIXUENGINE_STATUSBAR_COMPONENT_HPP

#include "ui/ui_component.hpp"

namespace taixu::editor {

class StatusBarComponent : public AbstractUIComponent {
public:
    void update() override {
        float const&   statusWindowHeight = ImGui::GetFrameHeight() * 1.3f;
        ImGuiViewport* viewport           = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(
                viewport->Pos.x,
                viewport->Pos.y + viewport->Size.y - statusWindowHeight));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, statusWindowHeight));
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags =
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking;
        ImGui::Begin("StatusBar", nullptr, windowFlags);
        float dy = ImGui::GetFontSize() * 0.15f;

        ImGui::SameLine(ImGui::GetIO().DisplaySize.x -
                        14.f * ImGui::GetFontSize());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - dy);
        ImGui::Text("FPS: 100");

        ImGui::End();
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_STATUSBAR_COMPONENT_HPP
