//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_DETAIL_COMPONENT_HPP
#define TAIXUENGINE_DETAIL_COMPONENT_HPP

#include "ui/ui_component.hpp"

#include "ImGuizmo.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "gameplay/player/perspective_camera.hpp"


namespace taixu::editor {
class DetailComponent : public IUIComponent {
public:
    ImGuizmo::OPERATION mCurrentGizmoOperation {ImGuizmo::OPERATION::TRANSLATE};
    ImGuizmo::MODE mCurrentGizmoMode{ImGuizmo::MODE::LOCAL};
    float matrixTranslation[3], matrixRotation[3], matrixScale[3];
    ImGuiWindowFlags gizmoWindowFlags = 0;

    void update() override {
        if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button("Open...")) {}
            ImGui::SameLine(0, 5.0f);
            ImGui::Text("aa");
        }

        if (ImGui::CollapsingHeader("Material")) {
            float color[3] = {1.0f, 2.0f, 3.0f};
            float f1       = 0.0f;
            float f2       = 0.0f;
            ImGui::ColorPicker3("Color", color,
                                ImGuiColorEditFlags_PickerHueWheel |
                                        ImGuiColorEditFlags_DisplayRGB);
            ImGui::SliderFloat("Roughness", &f1, 0.0f, 1.0f);
            ImGui::SliderFloat("Metallic", &f2, 0.0f, 1.0f);
        }

        if (ImGui::CollapsingHeader("Light")) {
            ImGui::Separator();
            ImGui::Text("Position");
            ImGui::Separator();
        }

        
        if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
            mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
            mCurrentGizmoOperation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
            mCurrentGizmoOperation = ImGuizmo::SCALE;
        if (ImGui::RadioButton("Universal", mCurrentGizmoOperation == ImGuizmo::UNIVERSAL))
            mCurrentGizmoOperation = ImGuizmo::UNIVERSAL;

        
        ImGui::InputFloat3("Tr", matrixTranslation);
        ImGui::InputFloat3("Rt", matrixRotation);
        ImGui::InputFloat3("Sc", matrixScale);
        

        if (mCurrentGizmoOperation != ImGuizmo::SCALE)
        {
            if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
            mCurrentGizmoMode = ImGuizmo::LOCAL;
            ImGui::SameLine();
            if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
            mCurrentGizmoMode = ImGuizmo::WORLD;
        }
    }

    void transformLisen(PerspectiveCamera *current_camera, float* matrix, bool editTransformDecomposition)
    {
        //int a= 0;
        
        glm::mat4 mat = glm::make_mat4(matrix);
        ImGuiIO& io = ImGui::GetIO();
        //float viewManipulateRight = io.DisplaySize.x;
        //float viewManipulateTop = 0;
        

        
        
        //viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
        //viewManipulateTop = ImGui::GetWindowPos().y;
        


        
        //ImGuizmo::DrawCubes(cameraView, cameraProjection, identityMatrix, 1);
        //ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);

        
    }

};
}// namespace taixu::editor

#endif//TAIXUENGINE_DETAIL_COMPONENT_HPP
