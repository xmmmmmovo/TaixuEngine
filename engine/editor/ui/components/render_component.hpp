//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "graphics/renderer.hpp"
#include "interface/component.hpp"

namespace taixu::editor {

class RenderComponent : public IUIComponent {
private:
    std::shared_ptr<cg::Renderer> m_renderer;

public:
    const float delta_time = 0.03333;
    void init() override {
        m_renderer = std::make_shared<cg::Renderer>();
        m_renderer->initialize();
    }

    void preUpdate() {}

    void update() override {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImVec2 size              = {viewportPanelSize.x, viewportPanelSize.y};

        m_renderer->resize(size.x, size.y);
        m_renderer->tick();
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        ImGui::Image(reinterpret_cast<void *>(m_renderer->getRenderResult()),
                     size, ImVec2(0, 1), ImVec2(1, 0));
    }
    void processInput(std::string input) { m_renderer->processInput(input);}
    void processInput(glm::vec2 mouse_pos) { m_renderer->processInput(mouse_pos); }
    void processInput(float scroll_yoffset) { m_renderer->processInput(scroll_yoffset); }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
