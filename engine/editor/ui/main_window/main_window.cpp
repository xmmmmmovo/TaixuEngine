//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include "spdlog/spdlog.h"

namespace taixu::editor {
void MainWindow::init() {
    spdlog::info("Main window start initWindow!");
    context_ptr->initWindow();
    context_ptr->setVsync(true);
    spdlog::info("Main window start finished!");
}

void MainWindow::preUpdate() {
    ImguiSurface::preUpdate();

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

    ImguiSurface::addWidget(WORLD_OBJ_COMPONENT_NAME,
                            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                                    world_object_component->update));
    ImguiSurface::addWidget(
            RENDER_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component->update));
    ImguiSurface::addWidget(
            DETAILS_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component->update));
    ImguiSurface::addWidget(
            FILE_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component->update));
    ImguiSurface::addWidget(
            STATUS_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component->update));
    ImguiSurface::addWidget(
            USEFUL_OBJ_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(useful_obj_component->update));
    ImguiSurface::addWidget(
            TOOLBAR_COMPONENT_NAME,
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(tool_bar_component->update),
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoNav);
}

void MainWindow::update() {
    preUpdate();
    ImguiSurface::update();
    context_ptr->swapBuffers();
}

void MainWindow::destroy() {
    ImguiSurface::destroy();
    context_ptr->destroy();
}

void MainWindow::setEngineRuntime(Engine* engine_runtime_ptr) {
    this->engine_runtime = engine_runtime_ptr;
    this->renderer       = engine_runtime_ptr->getRenderer();

    ImguiSurface::init(context_ptr->_window);
    render_component->setRenderer(renderer);
}

MainWindow::MainWindow(std::shared_ptr<WindowContext> const& context_ptr)
    : context_ptr(context_ptr) {
    this->menu_component->bindCallbacks(
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onNewProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onOpenProjectCb),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(onSaveProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onSaveAsProjectCb));
}

// for callbacks
void MainWindow::onNewProjectCb(std::string_view const& path) {}
void MainWindow::onOpenProjectCb(std::string_view const& path) {
    this->engine_runtime->loadProject(path);
}
void MainWindow::onSaveProjectCb() {}
void MainWindow::onSaveAsProjectCb(std::string_view const& path) {}

}// namespace taixu::editor