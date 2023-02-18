//
// Created by xmmmmmovo on 2023/2/12.
//

#include "render_component.hpp"

#include <glad/glad.h>

#include "frag_frag.h"
#include "graphics/render/shader.hpp"
#include "vert_vert.h"

namespace taixu::editor {
void RenderComponent::init() {
    m_renderer = std::make_shared<cg::Renderer>();
    m_renderer->initialize();
}

void RenderComponent::update() {
    m_renderer->tick();

    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImVec2 size               = {viewportPanelSize.x, viewportPanelSize.y};

    // Because I use the texture from OpenGL, I need to invert the V from the UV.
    ImGui::Image(reinterpret_cast<void *>(m_renderer->getRenderResult()), size,
                 ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}
}// namespace taixu::editor