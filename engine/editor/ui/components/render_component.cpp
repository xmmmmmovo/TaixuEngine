//
// Created by xmmmmmovo on 2023/2/12.
//

#include "render_component.hpp"

#include <glad/glad.h>

#include "frag_frag.h"
#include "graphics/render/shader.hpp"
#include "vert_vert.h"

namespace taixu::editor {

// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改
// 暂时先这么写，只是测试用，以后会改

cg::ShaderProgram *shaderProgram;
// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float              vertices[] = {
        -0.5f, -0.5f, 0.0f,// left
        0.5f,  -0.5f, 0.0f,// right
        0.0f,  0.5f,  0.0f // top
};
unsigned int VBO, VAO;
unsigned int fbo, bufferTexId, rbo;
ImVec2       size = {1366, 768};

void RenderComponent::init() {
    m_renderer = std::make_shared<cg::Renderer>();
    m_renderer->initialize();
}

void RenderComponent::update() {
    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImVec2 size              = {viewportPanelSize.x, viewportPanelSize.y};

    m_renderer->resize(size.x, size.y);
    m_renderer->tick();
    // Because I use the texture from OpenGL, I need to invert the V from the UV.
    ImGui::Image(reinterpret_cast<void *>(m_renderer->getRenderResult()), size,
                 ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}
}// namespace taixu::editor