//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "ImGuizmo.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/math/imvec2.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "imgui.h"
#include "management/graphics/render/framebuffer.hpp"
#include "management/graphics/renderer.hpp"
#include "management/input/input_system.hpp"
#include "management/scene/scene.hpp"
#include "spdlog/spdlog.h"
#include "ui/ui_component.hpp"
#include "ui/view_model.hpp"

namespace taixu::editor {

class RenderComponent : public AbstractUIComponent {
public:
    ImVec2 _render_size{0, 0};
    ImVec2 _previous_size{0, 0};
    ImRect _render_rect{};
    ImRect _menu_bar_rect{};

public:
    explicit RenderComponent(ViewModel *view_model)
        : AbstractUIComponent(view_model){};

    void update() override {
        if (ImGui::BeginMenuBar()) {
            ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x * 0.6f -
                                 ImGui::GetWindowHeight());

            if (ImGui::Button(ICON_FA_PLAY "Play")) {}
            if (ImGui::Button(ICON_FA_ARROWS_SPIN "Rotate")) {}
            if (ImGui::Button(ICON_FA_RIGHT_LEFT "Transform")) {}
            if (ImGui::Button(ICON_FA_MAGNIFYING_GLASS "Zoom")) {}

            ImGui::EndMenuBar();
        }

        _menu_bar_rect = ImGui::GetCurrentWindow()->MenuBarRect();
        _render_size   = ImGui::GetWindowSize();
        _render_size.y -= _menu_bar_rect.GetHeight();

        _render_rect.Min = ImGui::GetWindowPos();
        _render_rect.Min.x -= ImGui::GetMainViewport()->Pos.x;
        _render_rect.Min.y -= ImGui::GetMainViewport()->Pos.y;
        _render_rect.Min.y += _menu_bar_rect.GetHeight();

        _render_rect.Max.x = _render_rect.Min.x + _render_size.x;
        _render_rect.Max.y = _render_rect.Min.y + _render_size.y;

        if (_previous_size != _render_size) {
            spdlog::debug("Resize the framebuffer: _width {}, _height {}",
                          _render_size.x, _render_size.y);
            _previous_size = _render_size;
            _view_model->_framebuffer->resize(static_cast<int>(_render_size.x),
                                              static_cast<int>(_render_size.y));
        }

        ImGui::Image(reinterpret_cast<ImTextureID>(
                             _view_model->_framebuffer->getFBTextureID()),
                     _render_size, ImVec2(0, 1), ImVec2(1, 0));
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
