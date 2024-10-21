//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_STYLE_HPP
#define TAIXUENGINE_STYLE_HPP

#define IMGUI_ENABLE_FREETYPE
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

namespace taixu::editor {

/**
 * This class encapsulate the imgui c style api.
 *
 * @brief unfinished style class
 */
struct EditorStyle {
    EditorStyle() = default;
    EditorStyle(ImGuiCol idx, ImVec4 color, bool predicate = true) : mSet(predicate) {
        if (predicate) {
            ImGui::PushStyleColor(idx, color);
        }
    }

    EditorStyle(ImGuiCol idx, ImU32 color, bool predicate = true) : mSet(predicate) {
        if (predicate) {
            ImGui::PushStyleColor(idx, color);
        }
    }

    ~EditorStyle() {
        if (mSet) {
            ImGui::PopStyleColor();
        }
    }

private:
    bool mSet = false;
};

}// namespace taixu::editor

#endif// TAIXUENGINE_STYLE_HPP
