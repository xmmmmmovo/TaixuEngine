//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "core/math/imvec2.hpp"
#include "management/graphics/render/framebuffer.hpp"
#include "management/graphics/renderer.hpp"
#include "management/input/input_system.hpp"
#include "spdlog/spdlog.h"
#include "ui/ui_component.hpp"

namespace taixu::editor {

class RenderComponent : public IUIComponent {
public:
    IFrameBuffer *_framebuffer;
    ImVec2        _render_size{0, 0};
    ImVec2        _previous_size{0, 0};
    ImRect        _render_rect{};
    ImRect        _menu_bar_rect{};
    ImTextureID   _textureID;
    ImDrawList*   _drawList{nullptr};
    ImVec2 imagePos;
    ImVec2 imageEndPos;
    bool drawGrid{false};
    bool firstround{true};
    glm::mat4 viewmatrix{glm::mat4(0.0f)};
    glm::mat4 projectionmatrix{glm::mat4(0.0f)};
    glm::mat4 identity{glm::mat4(1.0f)};
    glm::mat4 selectedObjectTranform;

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

        //_textureID = reinterpret_cast<ImTextureID>(_framebuffer->getFBTextureID());

        

        // if(_drawList == nullptr)
        // {
        //     _drawList = ImGui::GetWindowDrawList();
        //     imagePos = ImGui::GetCursorScreenPos();
        //     imageEndPos;
        //     imageEndPos.x = imagePos.x + _render_size.x;
        //     imageEndPos.y = imagePos.y + _render_size.y;
        // }
        //if(drawGrid)
        //{
            _drawList = ImGui::GetWindowDrawList();
            imagePos = ImGui::GetCursorScreenPos();
            imageEndPos;
            imageEndPos.x = imagePos.x + _render_size.x;
            imageEndPos.y = imagePos.y + _render_size.y;

            ImGui::Image(
                reinterpret_cast<ImTextureID>(_framebuffer->getFBTextureID()),
                _render_size, ImVec2(0, 1), ImVec2(1, 0));
            if(drawGrid)
                updateImagewithGrid();
            // // 绘制网格
            // float gridSize = 10.0f;
            // ImVec2 gridPos = ImVec2((int)imagePos.x, (int)imagePos.y);
            // while (gridPos.y < imageEndPos.y)
            // {
            //     _drawList->AddLine(ImVec2(gridPos.x, gridPos.y), ImVec2(imageEndPos.x, gridPos.y), IM_COL32(255, 255, 255, 100));
            //     gridPos.y += gridSize;
            // }
            // while (gridPos.x < imageEndPos.x)
            // {
            //     _drawList->AddLine(ImVec2(gridPos.x, gridPos.y), ImVec2(gridPos.x, imageEndPos.y), IM_COL32(255, 255, 255, 100));
            //     gridPos.x += gridSize;
            // }
        //}

        }

        void updateImagewithGrid()
        {
            ImGuizmo::SetDrawlist(_drawList);
            ImGuizmo::SetRect(
            imagePos.x,imagePos.y,
            imageEndPos.x,imageEndPos.y
            );
            //glm::mat4 model(1.0f);
            //model[3] = selectedObjectTranform[3];
            float *cameraView = glm::value_ptr(viewmatrix);
            float *cameraProjection = glm::value_ptr(projectionmatrix);
            float *identityMatrix = glm::value_ptr(identity);
            float *modelMatrix = glm::value_ptr(selectedObjectTranform);
            //ImGuizmo::DrawCubes(cameraView, cameraProjection, modelMatrix, 1);
            //ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);

            // // 绘制网格
            // float gridSize = 10.0f;
            // ImVec2 gridPos = ImVec2((int)imagePos.x, (int)imagePos.y);
            // while (gridPos.y < imageEndPos.y)
            // {
            //     _drawList->AddLine(ImVec2(gridPos.x, gridPos.y), ImVec2(imageEndPos.x, gridPos.y), IM_COL32(255, 255, 255, 100));
            //     gridPos.y += gridSize;
            // }
            // while (gridPos.x < imageEndPos.x)
            // {
            //     _drawList->AddLine(ImVec2(gridPos.x, gridPos.y), ImVec2(gridPos.x, imageEndPos.y), IM_COL32(255, 255, 255, 100));
            //     gridPos.x += gridSize;
            // }
        }

    };
}// namespace taixu::editor

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
