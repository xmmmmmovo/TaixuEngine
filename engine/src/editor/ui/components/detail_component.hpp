//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_DETAIL_COMPONENT_HPP
#define TAIXUENGINE_DETAIL_COMPONENT_HPP

#include "ui/common/ui_component.hpp"
#include "ui/components/render_component.hpp"

#include "imgui/imzmo/ImGuizmo.h"
#include "imgui_internal.h"

#include "ui/widgets/slider.hpp"


namespace taixu::editor {

class DetailComponent : public AbstractUIComponent {
private:
    static std::string_view constexpr DETAILS_COMPONENT_NAME{"Components Details"};

public:
    explicit DetailComponent(ViewModel& view_model) : AbstractUIComponent(view_model) {
    }


    void update() {
        if (ImGui::Begin(DETAILS_COMPONENT_NAME.data(), nullptr, ImGuiWindowFlags_None)) {
            if (!_view_model.is_entity_selected) {
                ImGui::End();
                return;
            }

            ImGui::End();
        }

        //        auto ecs =
        //        _view_model.engine_runtime_ptr->getECSCoordinator();
        //
        //        if (ecs == nullptr || ecs->getEntityCount() == 0) { return; }
        //
        //        if (ecs->getEntityCount() < _view_model.selected_entity) {
        //            _view_model.is_entity_selected = false;
        //        }
        //
        //        if
        //        (ecs->anyOf<TransformComponent>(_view_model.selected_entity))
        //        {
        //            auto& trans = ecs->getComponent<TransformComponent>(
        //                    _view_model.selected_entity);
        //
        //            if (ImGui::CollapsingHeader("Transform",
        //                                        ImGuiTreeNodeFlags_DefaultOpen))
        //                                        {
        //                ImGui::Text("Transform Control");
        //
        //                // imguizmo Mode Selection
        //                ImGui::RadioButton(
        //                        "Local",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_mode),
        //                        ImGuizmo::MODE::LOCAL);
        //                ImGui::SameLine();
        //                ImGui::RadioButton(
        //                        "World",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_mode),
        //                        ImGuizmo::MODE::WORLD);
        //                ImGui::Separator();
        //
        //                // imguizmo Operation Selection
        //                ImGui::RadioButton(
        //                        "Translate",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_operation),
        //                        ImGuizmo::OPERATION::TRANSLATE);
        //                ImGui::SameLine();
        //                ImGui::RadioButton(
        //                        "Rotate",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_operation),
        //                        ImGuizmo::OPERATION::ROTATE);
        //                ImGui::SameLine();
        //                ImGui::RadioButton(
        //                        "Scale",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_operation),
        //                        ImGuizmo::OPERATION::SCALE);
        //                ImGui::RadioButton(
        //                        "ScaleUniversal",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_operation),
        //                        ImGuizmo::OPERATION::SCALEU);
        //                ImGui::SameLine();
        //                ImGui::RadioButton(
        //                        "Universal",
        //                        reinterpret_cast<int*>(&_view_model.guizmo_operation),
        //                        ImGuizmo::OPERATION::UNIVERSAL);
        //                ImGui::Separator();
        //
        //                // Translation
        //                bool const t_changed =
        //                        buildVec3Slider("Translation",
        //                        trans.translate());
        //
        //                // Rotation
        //                glm::vec3 euler_rotation =
        //                        glm::degrees(glm::eulerAngles(trans.rotation()));
        //                glm::vec3 const euler_rotation_old = euler_rotation;
        //
        //                bool const r_changed =
        //                        buildVec3Slider("Rotation", euler_rotation);
        //
        //                // 判断是否需要翻转
        //                if (r_changed) {
        //                    float new_y_rot = euler_rotation.y;
        //
        //                    if (trans.inversed()) {
        //                        glm::vec3 rotDiff = euler_rotation_old -
        //                        euler_rotation; rotDiff *= -1.f;
        //                        euler_rotation = euler_rotation_old - rotDiff;
        //                        new_y_rot      = euler_rotation.y;
        //                    }
        //
        //                    if (new_y_rot < -90.f) {
        //                        trans.set_inversed(!trans.inversed());
        //                        euler_rotation.x -= 180.f;
        //                        euler_rotation.y += 180.f;
        //                        euler_rotation.y *= -1.f;
        //                        euler_rotation.z += 180.f;
        //                    } else if (new_y_rot > 90.f) {
        //                        trans.set_inversed(!trans.inversed());
        //                        euler_rotation.x -= -180.f;
        //                        euler_rotation.y += -180.f;
        //                        euler_rotation.y *= -1.f;
        //                        euler_rotation.z += -180.f;
        //                    }
        //                    trans.set_rotation(glm::quat(glm::radians(euler_rotation)));
        //                }
        //
        //                // Scaling
        //                bool const s_changed = buildVec3Slider("Scaling",
        //                trans.scale(),
        //                                                       glm::vec3{1.0f});
        //                ImGui::Separator();
        //
        //                if (t_changed || r_changed || s_changed) {
        //                    trans.makeTransformMatrix();
        //                }
        //            }
        //        }
        //
        //        if
        //        (ecs->anyOf<RenderableComponent>(_view_model.selected_entity))
        //        {}
    }
};
}// namespace taixu::editor

#endif// TAIXUENGINE_DETAIL_COMPONENT_HPP
