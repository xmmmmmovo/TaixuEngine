//
// Created by xmmmmmovo on 2023/5/20.
//

#ifndef ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP
#define ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP

#include <imgui.h>
#include <imgui_internal.h>

#include "string"

namespace taixu::editor {

constexpr float TOOLTIP_TRESH_HOLD = 0.5f;

inline void buildTooltip(const std::string &tooltip,
                         float              tresh_hold = TOOLTIP_TRESH_HOLD) {
    if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > tresh_hold) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(tooltip.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

}// namespace taixu::editor

#endif//ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP
