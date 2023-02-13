//
// Created by xmmmmmovo on 2023/2/12.
//

#include "control_component.hpp"

#include <spdlog/spdlog.h>

namespace taixu::editor {
void ControlComponent::init() {}

void ControlComponent::update() {
    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::Button("Open..."))
        {
        }
        ImGui::SameLine(0, 5.0f);
        ImGui::Text("aa");
    }

    if (ImGui::CollapsingHeader("Material"))
    {
        float color[3] = {1.0f, 2.0f, 3.0f};
        float f1 = 0.0f;
        float f2 = 0.0f;
        ImGui::ColorPicker3("Color", color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        ImGui::SliderFloat("Roughness", &f1, 0.0f, 1.0f);
        ImGui::SliderFloat("Metallic", &f2, 0.0f, 1.0f);
    }

    if (ImGui::CollapsingHeader("Light"))
    {

        ImGui::Separator();
        ImGui::Text("Position");
        ImGui::Separator();
    }

    ImGui::End();
}
}// namespace taixu::editor