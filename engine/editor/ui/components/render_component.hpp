//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "core/math/imvec2.hpp"
#include "graphics/render/framebuffer.hpp"
#include "graphics/render_context.hpp"
#include "graphics/renderer.hpp"
#include "gui/input_system.hpp"
#include "ui/ui_component.hpp"

namespace taixu::editor {

class RenderComponent : public IUIComponent {
public:
    IFrameBuffer *_framebuffer;
    ImVec2        _render_size{};
    ImVec2        _previous_size{};
    ImRect        _render_rect{};
    ImRect        _menu_bar_rect{};

public:
    void update() override {
        if (ImGui::BeginMenuBar()) {
            float const size = ImGui::GetWindowHeight() - 4.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) -
                                 (size * 0.5f));

            if (ImGui::Button(ICON_FA_PLAY "Play")) {}
            ImGui::EndMenuBar();
        }

        _previous_size = _render_size;

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
            _framebuffer->resize(static_cast<int>(_render_size.x),
                                 static_cast<int>(_render_size.y));
        }

        ImGui::Image(
                reinterpret_cast<ImTextureID>(_framebuffer->getFrameBufferID()),
                _render_size, ImVec2(0, 1), ImVec2(1, 0));
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
