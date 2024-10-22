//
// Created by xmmmmmovo on 2023/5/20.
//

#ifndef ENGINE_EDITOR_UI_WIDGETS_SLIDER_HPP
#define ENGINE_EDITOR_UI_WIDGETS_SLIDER_HPP

#include <glm/glm.hpp>

#include <taixu/common/base/macro.hpp>

#include "tooltip.hpp"

namespace taixu::editor {

TX_INLINE bool buildVec3Slider(const std::string& label, glm::vec3& values,
                               const glm::vec3 reset_values = glm::vec3{0.f}, float column_width = 100.0f) {
    bool           b_value_changed = false;
    ImGuiIO const& io              = ImGui::GetIO();
    auto           bold_font       = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, column_width);
    ImGui::TextUnformatted(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f});

    float const  line_height = (GImGui->Font->FontSize * bold_font->Scale) + GImGui->Style.FramePadding.y * 2.f;
    ImVec2 const button_size = {line_height + 3.f, line_height};

    // X
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.2f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.f});
    ImGui::PushFont(bold_font);
    if (ImGui::Button("X", button_size)) {
        values.x        = reset_values.x;
        b_value_changed = true;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    b_value_changed |= ImGui::DragFloat("##X", &values.x, 0.1f);
    ImGui::PopItemWidth();
    buildTooltip(std::to_string(values.x));
    ImGui::SameLine();

    // Y
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.f});
    ImGui::PushFont(bold_font);
    if (ImGui::Button("Y", button_size)) {
        values.y        = reset_values.y;
        b_value_changed = true;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    b_value_changed |= ImGui::DragFloat("##Y", &values.y, 0.1f);
    ImGui::PopItemWidth();
    buildTooltip(std::to_string(values.y));
    ImGui::SameLine();

    // Z
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.f});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.f});
    ImGui::PushFont(bold_font);
    if (ImGui::Button("Z", button_size)) {
        values.z        = reset_values.z;
        b_value_changed = true;
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    b_value_changed |= ImGui::DragFloat("##Z", &values.z, 0.1f);
    ImGui::PopItemWidth();
    buildTooltip(std::to_string(values.z));

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();

    return b_value_changed;
}
}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_WIDGETS_SLIDER_HPP
