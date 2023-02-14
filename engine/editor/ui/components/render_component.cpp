//
// Created by xmmmmmovo on 2023/2/12.
//

#include "render_component.hpp"

// 暂时先这么写，只是测试用，以后会改
#include "frag_frag.h"
#include "graphics/render/shader.hpp"
#include "vert_vert.h"

namespace taixu::editor {

// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改

void RenderComponent::init() {
    auto shaderProgram = cg::ShaderProgram(VERT_VERT, FRAG_FRAG);
}

void RenderComponent::update() {
    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    ImGui::End();
}
}// namespace taixu::editor