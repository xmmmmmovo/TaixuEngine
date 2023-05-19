//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_DETAIL_COMPONENT_HPP
#define TAIXUENGINE_DETAIL_COMPONENT_HPP

#include "management/ecs/components/transform/transform_component.hpp"
#include "ui/ui_component.hpp"

#include "ImGuizmo.h"
#include "gameplay/player/camera/perspective_camera.hpp"
#include "imgui.h"
#include "imgui_internal.h"


namespace taixu::editor {
class DetailComponent : public AbstractUIComponent {
public:
    explicit DetailComponent(ViewModel *view_model)
        : AbstractUIComponent(view_model) {}

    void update() override {
        auto ecs = _view_model->_engine_runtime_ptr->getECSCoordinator();

        if (ecs == nullptr || ecs->getEntityCount() == 0) { return; }

        if (ecs->getEntityCount() < _view_model->_selected_entity) {
            _view_model->_selected_entity = 0;
        }

        if (ecs->anyOf<TransformComponent>(_view_model->_selected_entity)) {
            auto &trans = ecs->getComponent<TransformComponent>(
                    _view_model->_selected_entity);

            if (ImGui::CollapsingHeader("Transform",
                                        ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Text("Transform Control");

                // Translation
                ImGui::Text("Translation");
                ImGui::DragFloat3("Position", &trans.translate().x, 0.1f);

                // Rotation
                ImGui::Text("Rotation");
                glm::vec3 eulerRotation =
                        glm::degrees(glm::eulerAngles(trans.rotation()));
                ImGui::DragFloat3("Rotation", &eulerRotation.x, 0.5f, -360.0f,
                                  360.0f);
                trans.set_rotation(glm::quat(glm::radians(eulerRotation)));

                // Scaling
                ImGui::Text("Scaling");
                ImGui::DragFloat3("Scale", &trans.scale().x, 0.1f);
                ImGui::Separator();
            }
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
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_DETAIL_COMPONENT_HPP
