//
// Created by xmmmmmovo on 2023/2/12.
//

#include "render_component.hpp"

namespace taixu::editor {
void RenderComponent::init() {}
void RenderComponent::update() {
    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    ImGui::End();
}
}// namespace taixu::editor