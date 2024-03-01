//
// Created by xmmmmmovo on 2023/3/25.
//

#ifndef TAIXUENGINE_STATUSBAR_COMPONENT_HPP
#define TAIXUENGINE_STATUSBAR_COMPONENT_HPP

#include "ui/common/ui_component.hpp"

namespace taixu::editor {

class StatusBarComponent : public AbstractUIComponent {
private:
    static std::string_view constexpr STATUS_COMPONENT_NAME{"EnumStatus"};

public:
    explicit StatusBarComponent(ViewModel* view_model)
        : AbstractUIComponent(view_model,
                              {.name           = STATUS_COMPONENT_NAME,
                               .component_type = EnumImguiComponentType::WIDGET,
                               .update_func    = [this]() { this->update(); },
                               .end_call_back  = nullptr}) {}

    void update() {
        float const&   status_window_height = ImGui::GetFrameHeight() * 1.3f;
        ImGuiViewport* viewport             = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(
                ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y -
                                                status_window_height));
        ImGui::SetNextWindowSize(
                ImVec2(viewport->Size.x, status_window_height));
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags const window_flags =
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking;
        ImGui::Begin("StatusBar", nullptr, window_flags);
        float const dy = ImGui::GetFontSize() * 0.15f;

        ImGui::SameLine(ImGui::GetIO().DisplaySize.x -
                        14.f * ImGui::GetFontSize());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - dy);
        ImGui::Text("FPS: 100");

        ImGui::End();
    }
};

}// namespace taixu::editor

#endif// TAIXUENGINE_STATUSBAR_COMPONENT_HPP
