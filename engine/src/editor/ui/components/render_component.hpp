//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "common/log/logger.hpp"
#include <IconsFontAwesome6.h>
#include <ImGuizmo.h>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <imgui.h>

#include "common/math/imvec2.hpp"
#include "ui/common/ui_component.hpp"
#include "ui/common/view_model.hpp"

namespace taixu::editor {

class RenderComponent : public AbstractUIComponent {
public:
    ImVec2 _render_size{0, 0};
    ImVec2 _previous_size{0, 0};
    ImRect _render_rect{};
    ImRect _menu_bar_rect{};

    float _aspect_ratio{0.0f};

public:
    explicit RenderComponent(ViewModel* view_model)
        : AbstractUIComponent(view_model){};

    void update() override {
        if (ImGui::BeginMenuBar()) {
            ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x * 0.6f -
                                 ImGui::GetWindowHeight());

            //            if (_view_model->engine_runtime_ptr->getState() ==
            //                EngineState::EDITORMODE) {
            if (ImGui::Button(ICON_FA_PLAY "Play")) {}
            //            } else {
            //                if (ImGui::Button(ICON_FA_STOP "Stop")) {}
            //            }
            ImGui::EndMenuBar();
        }

        _menu_bar_rect = ImGui::GetCurrentWindow()->MenuBarRect();
        _render_size   = ImGui::GetWindowSize();
        _render_size.y -= _menu_bar_rect.GetHeight();

        _render_rect.Min = ImGui::GetWindowPos();
        _render_rect.Min.x -= ImGui::GetMainViewport()->Pos.x;
        _render_rect.Min.y -= ImGui::GetMainViewport()->Pos.y;
        _render_rect.Min.y += _menu_bar_rect.GetHeight();

        _render_rect.Max.x = _render_rect.Min.x + _render_size.x;
        _render_rect.Max.y = _render_rect.Min.y + _render_size.y;

        if (_previous_size != _render_size) {
            INFO_LOG("Resize the framebuffer: _width {}, _height {}",
                     _render_size.x, _render_size.y);
            _previous_size = _render_size;
            //            _view_model->framebuffer->resize(static_cast<int>(_render_size.x),
            //                                             static_cast<int>(_render_size.y));
            _aspect_ratio  = _render_size.x / _render_size.y;
        }

        //        ImGui::Image(reinterpret_cast<ImTextureID>(0), _render_size,
        //                     ImVec2(0, 1), ImVec2(1, 0));

        if (_view_model->is_entity_selected) {
            //            ImGuizmo::SetOrthographic(false);
            //            ImGuizmo::SetDrawlist();
            //
            //            ImGuizmo::SetRect(ImGui::GetWindowPos().x,
            //            ImGui::GetWindowPos().y,
            //                              _render_size.x, _render_size.y);
            //
            //            // Camera
            //            auto* camera =
            //                    _view_model->engine_runtime_ptr->getScene()->_camera.get();
            //
            //            if (camera->aspect_ratio() != _aspect_ratio) {
            //                camera->set_aspect_ratio(_aspect_ratio);
            //            }
            //
            //            const glm::mat4& camera_projection =
            //            camera->getProjectionMatrix(); const glm::mat4&
            //            camera_view       = camera->getViewMatrix();
            //
            //            // Entity transform
            //            auto& tc =
            //                    _view_model->engine_runtime_ptr->getScene()
            //                            ->_ecs_coordinator.getComponent<TransformComponent>(
            //                                    _view_model->selected_entity);
            //            glm::mat4& transform = tc.transform();
            //
            //            // 绘制的时候, 需要传入camera的v和p矩阵,
            //            // 再传入要看物体的transform矩阵即可, 就会绘制出
            //            其localGizmos
            //            ImGuizmo::Manipulate(glm::value_ptr(camera_view),
            //                                 glm::value_ptr(camera_projection),
            //                                 _view_model->guizmo_operation,
            //                                 _view_model->guizmo_mode,
            //                                 glm::value_ptr(transform));
            //
            //            if (ImGuizmo::IsUsing()) {
            //                static glm::vec3 unused1;
            //                static glm::vec4 unused2;
            //
            //                glm::decompose(transform, tc.scale(),
            //                tc.rotation(),
            //                               tc.translate(), unused1, unused2);
            //            }
        }
    }
};
}// namespace taixu::editor

#endif// TAIXUENGINE_RENDER_COMPONENT_HPP
