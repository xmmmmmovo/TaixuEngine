/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "render_component.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui/icons/IconsLucide.h>
#include <imgui_internal.h>

#include <taixu/common/log/logger.hpp>

namespace taixu::editor {

static constexpr ImGuiWindowFlags RENDER_FLAGS{ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar};
static constexpr ImGuiWindowFlags SIDE_TOOLBAR_FLAGS{
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus};
static constexpr std::string_view RENDER_COMPONENT_NAME{"Scene"};
static constexpr std::string_view SIDE_TOOLBAR_NAME{"##ViewportSideToolbar"};

void RenderComponent::buildSideToolBar() {
    static constexpr ImVec2               SIDE_TOOLBAR_ITEM_SIZE{60, 60};
    static constexpr ImVec2               SIDE_TOOLBAR_SELECTABLE_ALIGN{0.5, 0.5};
    static constexpr int8_t               SIDE_TOOLBAR_ITEMS{4};
    static constexpr ImGuiSelectableFlags SELECTABLE_FLAGS{ImGuiSelectableFlags_NoPadWithHalfSpacing};
    static constexpr ImGuiButtonFlags     BUTTON_FLAGS{ImGuiButtonFlags_MouseButtonMiddle};

    ImGuiStyle const& style = ImGui::GetStyle();

    // Toolbar
    const ImVec2 toolbar_pos = ImGui::GetWindowPos() + ImGui::GetCursorPos();

    const ImVec2 toolbar_size = {SIDE_TOOLBAR_ITEM_SIZE.x + style.WindowPadding.x * 2.0f,//
                                 SIDE_TOOLBAR_ITEM_SIZE.y * SIDE_TOOLBAR_ITEMS + style.WindowPadding.y * 2.0f};
    ImGui::SetNextWindowPos(toolbar_pos);
    ImGui::SetNextWindowSize(toolbar_size);

    if (ImGui::Begin(SIDE_TOOLBAR_NAME.data(), nullptr, SIDE_TOOLBAR_FLAGS)) {
        // Bring the toolbar window always on top.
        ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, SIDE_TOOLBAR_SELECTABLE_ALIGN);

        if (ImGui::Selectable(ICON_LC_MOUSE_POINTER_2, _view_model.moving_state == MovingState::SELECT,
                              SELECTABLE_FLAGS, SIDE_TOOLBAR_ITEM_SIZE)) {
            _view_model.moving_state = MovingState::SELECT;
        }
        if (ImGui::Selectable(ICON_LC_MOVE, _view_model.moving_state == MovingState::MOVING, SELECTABLE_FLAGS,
                              SIDE_TOOLBAR_ITEM_SIZE)) {
            _view_model.moving_state = MovingState::MOVING;
        }

        ImGui::Separator();

        if (ImGui::ButtonEx(ICON_LC_PLAY, SIDE_TOOLBAR_ITEM_SIZE, BUTTON_FLAGS)) {}

        ImGui::PopStyleVar();// ImGuiStyleVar_SelectableTextAlign
        ImGui::End();
    }
}
void RenderComponent::update() {

    ImGui::SetNextWindowClass(&_window_class);
    if (ImGui::Begin(RENDER_COMPONENT_NAME.data(), nullptr, RENDER_FLAGS)) {
        buildSideToolBar();
        ImGui::End();
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
        INFO_LOG("Resize the framebuffer: _width {}, _height {}", _render_size.x, _render_size.y);
        _previous_size = _render_size;
        //            _view_model.framebuffer->resize(static_cast<int>(_render_size.x),
        //                                             static_cast<int>(_render_size.y));
        _aspect_ratio  = _render_size.x / _render_size.y;
    }

    //        ImGui::Image(reinterpret_cast<ImTextureID>(0), _render_size,
    //                     ImVec2(0, 1), ImVec2(1, 0));

    if (_view_model.is_entity_selected) {
        //            ImGuizmo::SetOrthographic(false);
        //            ImGuizmo::SetDrawlist();
        //
        //            ImGuizmo::SetRect(ImGui::GetWindowPos().x,
        //            ImGui::GetWindowPos().y,
        //                              _render_size.x, _render_size.y);
        //
        //            // Camera
        //            auto* camera =
        //                    _view_model.engine_runtime_ptr->getScene()->_camera.get();
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
        //                    _view_model.engine_runtime_ptr->getScene()
        //                            ->_ecs_coordinator.getComponent<TransformComponent>(
        //                                    _view_model.selected_entity);
        //            glm::mat4& transform = tc.transform();
        //
        //            // 绘制的时候, 需要传入camera的v和p矩阵,
        //            // 再传入要看物体的transform矩阵即可, 就会绘制出
        //            其localGizmos
        //            ImGuizmo::Manipulate(glm::value_ptr(camera_view),
        //                                 glm::value_ptr(camera_projection),
        //                                 _view_model.guizmo_operation,
        //                                 _view_model.guizmo_mode,
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

}// namespace taixu::editor
