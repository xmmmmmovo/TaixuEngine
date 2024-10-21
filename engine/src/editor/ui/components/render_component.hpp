//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include <imgui.h>

#include "ui/common/ui_component.hpp"
#include "ui/common/view_model.hpp"

namespace taixu::editor {

class RenderComponent : public AbstractUIComponent {
private:
    ImGuiWindowClass _window_class{};

    void buildSideToolBar();

public:
    ImVec2 _render_size{0, 0};
    ImVec2 _previous_size{0, 0};
    ImRect _render_rect{};
    ImRect _menu_bar_rect{};

    float _aspect_ratio{0.0f};

public:
    explicit RenderComponent(ViewModel& view_model) : AbstractUIComponent(view_model) {
        _window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    }

    void update();
};
}// namespace taixu::editor

#endif// TAIXUENGINE_RENDER_COMPONENT_HPP
