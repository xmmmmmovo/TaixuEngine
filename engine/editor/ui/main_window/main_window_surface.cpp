//
// Created by xmmmmmovo on 2023/3/2.
//

#include "main_window_surface.hpp"

#include "core/utils/function_utils.hpp"
#include "main_window.hpp"

namespace taixu::editor {

void MainWindowSurface::init() {
    this->imgui_surface.init(parent_window->window);
    render_component->setRenderer(parent_window->renderer);
}

void MainWindowSurface::preUpdate() {
    imgui_surface.preUpdate();

    // Create the docking environment
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
            ImGuiConfigFlags_NoMouseCursorChange |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Editor Menu", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dock_space_id = ImGui::GetID(DOCK_SPACE_NAME);

    ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f));

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            menu_component->update();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    menu_component->processFileDialog();

    imgui_surface.addWidget(WORLD_OBJ_COMPONENT_NAME,
                            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                                    world_object_component->update));
    imgui_surface.addWidget(
            RENDER_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component->update));
    imgui_surface.addWidget(
            DETAILS_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component->update));
    imgui_surface.addWidget(
            FILE_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component->update));
    imgui_surface.addWidget(
            STATUS_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component->update));
    imgui_surface.addWidget(
            USEFUL_OBJ_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(useful_obj_component->update));
    imgui_surface.addWidget(
            TOOLBAR_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(tool_bar_component->update),
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoScrollWithMouse);
}

void MainWindowSurface::destroy() { this->imgui_surface.destroy(); }

void MainWindowSurface::update() { this->imgui_surface.update(); }

}// namespace taixu::editor