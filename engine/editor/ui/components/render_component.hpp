//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "ImGuizmo.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/math/imvec2.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "imgui.h"
#include "management/graphics/render/framebuffer.hpp"
#include "management/graphics/renderer.hpp"
#include "management/input/input_system.hpp"
#include "management/scene/scene.hpp"
#include "spdlog/spdlog.h"
#include "ui/ui_component.hpp"

namespace taixu::editor {

class RenderComponent : public IUIComponent {
public:
    IFrameBuffer       *_framebuffer;
    ImVec2              _render_size{0, 0};
    ImVec2              _previous_size{0, 0};
    ImRect              _render_rect{};
    ImRect              _menu_bar_rect{};
    ImTextureID         _textureID;
    ImDrawList         *_drawList{nullptr};
    ImVec2              imagePos;
    ImVec2              imageEndPos;
    glm::mat4           viewmatrix{glm::mat4(0.0f)};
    glm::mat4           projectionmatrix{glm::mat4(0.0f)};
    glm::mat4           identity{glm::mat4(1.0f)};
    glm::mat4           selectedObjectTranform;
    ImGuizmo::OPERATION mCurrentGizmoOperation{ImGuizmo::OPERATION::TRANSLATE};
    ImGuizmo::MODE      mCurrentGizmoMode{ImGuizmo::MODE::WORLD};
    float               matrixTranslation[3], matrixRotation[3], matrixScale[3];
    glm::mat4           delta{glm::mat4(1.0)};
    Scene              *current_scene{nullptr};

public:
    void update() override {


        if (ImGui::BeginMenuBar()) {
            float const size = ImGui::GetWindowHeight() - 4.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) -
                                 (size * 0.5f));

            if (ImGui::Button(ICON_FA_PLAY "Play")) {}
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
            spdlog::debug("Resize the framebuffer: _width {}, _height {}",
                          _render_size.x, _render_size.y);
            _previous_size = _render_size;
            _framebuffer->resize(static_cast<int>(_render_size.x),
                                 static_cast<int>(_render_size.y));
        }

        //float ratio = _render_size.x/_render_size.y;
        _drawList = ImGui::GetWindowDrawList();
        imagePos  = ImGui::GetCursorScreenPos();

        imageEndPos.x = imagePos.x + _render_size.x;
        imageEndPos.y = imagePos.y + _render_size.y;

        ImGui::Image(
                reinterpret_cast<ImTextureID>(_framebuffer->getFBTextureID()),
                _render_size, ImVec2(0, 1), ImVec2(1, 0));


        //ImGuizmo::BeginFrame();

        updateTrans();
    }

    void updateTrans() {
        ImGuizmo::BeginFrame();
        ImGuizmo::SetDrawlist();
        ImGuiIO &io = ImGui::GetIO();
        

        ImGuizmo::SetRect(imagePos.x, imagePos.y, imageEndPos.x, imageEndPos.y);

        float *cameraView       = glm::value_ptr(viewmatrix);
        float *cameraProjection = glm::value_ptr(projectionmatrix);
        float *identityMatrix   = glm::value_ptr(identity);
        float *modelMatrix      = glm::value_ptr(selectedObjectTranform);

        glm::mat4 MVP = selectedObjectTranform * viewmatrix * projectionmatrix;

        float *mvp             = glm::value_ptr(MVP);
        float  deltaMatrix[16] = {1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
                                  0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};

        ImGuizmo::Manipulate(cameraView, cameraProjection,
                             mCurrentGizmoOperation, mCurrentGizmoMode,
                             modelMatrix, deltaMatrix);

        if (mCurrentGizmoOperation == ImGuizmo::OPERATION::ROTATE)
            delta = glm::make_mat4(deltaMatrix);
        else
            delta = glm::make_mat4(modelMatrix);
        if (current_scene != nullptr) { operationCallback(); }
    }

    void operationCallback() {
        auto &trans = current_scene->_ecs_coordinator
                              .getComponent<TransformComponent>(0);

        if (_drawList != nullptr) {

            glm::mat4 temp = delta;

            glm::vec3 translate, scale, skew;
            glm::vec4 tempPerspective;
            glm::quat tempOrientation;
            glm::decompose(temp, scale, tempOrientation, translate, skew,
                           tempPerspective);
            if (mCurrentGizmoOperation == ImGuizmo::OPERATION::TRANSLATE) {
                //translate = translate + trans._position;
                trans.setPosition(translate);
            } else if (mCurrentGizmoOperation == ImGuizmo::OPERATION::ROTATE) {
                trans.setRotation(temp);
            } else if (mCurrentGizmoOperation == ImGuizmo::OPERATION::SCALE) {
                trans.setScale(scale);
            }
        }
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
