//
// Created by xmmmmmovo on 2023/5/20.
//

#ifndef ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP
#define ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP

#include <imgui.h>
#include <imgui_internal.h>

#include <taixu/common/base/macro.hpp>

namespace taixu::editor {

constexpr float TOOLTIP_TRESH_HOLD = 0.5f;

TX_INLINE void buildTooltip(const std::string& tooltip, float tresh_hold = TOOLTIP_TRESH_HOLD) {
    static constexpr float WRAP_POS_SHIFT = 35.0f;

    if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > tresh_hold) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * WRAP_POS_SHIFT);
        ImGui::TextUnformatted(tooltip.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_WIDGETS_TOOLTIP_HPP
