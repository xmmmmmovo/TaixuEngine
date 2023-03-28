//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "graphics/renderer.hpp"
#include "gui/input_system.hpp"
#include "ui/ui_component.hpp"

namespace taixu::editor {

class RenderComponent : public IUIComponent {
public:
    std::shared_ptr<Renderer> _renderer;
    ImVec2                    _render_size;
    ImRect                    _render_rect;
    ImRect                    _menu_bar_rect;

public:
    void update() override {
        if (ImGui::BeginMenuBar()) {
            float size = ImGui::GetWindowHeight() - 4.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) -
                                 (size * 0.5f));

            if (ImGui::Button(ICON_FA_PLAY "Play")) {}
            ImGui::EndMenuBar();
        }

        _menu_bar_rect = ImGui::GetCurrentWindow()->MenuBarRect();
        _render_size   = ImGui::GetWindowSize();
        _render_size.y -= _menu_bar_rect.GetHeight() + 8;

        _render_rect.Min = ImGui::GetWindowPos();
        _render_rect.Min.x -= ImGui::GetMainViewport()->Pos.x;
        _render_rect.Min.y -= ImGui::GetMainViewport()->Pos.y;
        _render_rect.Min.y += _menu_bar_rect.GetHeight();

        _render_rect.Max.x = _render_rect.Min.x + _render_size.x;
        _render_rect.Max.y = _render_rect.Min.y + _render_size.y;

        _renderer->resize(_render_size.x, _render_size.y);
        
        // TODO:???? ????????
        InputSystem::getInstance().processInput();
        _renderer->tick();
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image(reinterpret_cast<void*>(_renderer->getRenderResult()),
                     _render_size, ImVec2(0, 1), ImVec2(1, 0));
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
