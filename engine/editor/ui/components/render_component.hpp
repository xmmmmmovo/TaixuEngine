//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "interface/component.hpp"
#include "graphics/renderer.hpp"

namespace taixu::editor {

class RenderComponent : public IComponent {
public:
    void init() override;
    void update() override;

private:
    std::shared_ptr<cg::Renderer> m_renderer;
    void init() override {
        m_renderer = std::make_shared<cg::Renderer>();
        m_renderer->initialize();
    }
    void update() override {
        m_renderer->tick();

        ImGui::Begin("Scene");

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImVec2 size               = {viewportPanelSize.x, viewportPanelSize.y};

        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image(reinterpret_cast<void *>(m_renderer->getRenderResult()), size,
                     ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
