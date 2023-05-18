//
// Created by xmmmmmovo on 2023/2/12.
//
#include "glm/glm.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include "main_window.hpp"
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "core/base/path.hpp"
#include "gameplay/gui/imgui_surface.hpp"

#include "GraphEditor.h"

namespace taixu::editor {
void MainWindow::init() {
    spdlog::info("Main window init start!");

    _context_ptr->registerOnMouseButtonFn(
            [this](int button, int action, int /*mods*/) {
                if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
                    if (_view_model._renderer->move_mode()) {
                        _view_model._renderer->set_move_mode(false);
                        glfwSetInputMode(_context_ptr->_window, GLFW_CURSOR,
                                         GLFW_CURSOR_NORMAL);
                    } else {
                        if (isCursorInRenderComponent()) {
                            _view_model._renderer->set_move_mode(true);
                            glfwSetInputMode(_context_ptr->_window, GLFW_CURSOR,
                                             GLFW_CURSOR_DISABLED);
                        }
                    }
                }
            });

    spdlog::info("Main window init finished!");
}

void MainWindow::preUpdate() {
    ImguiSurface::preUpdate();

#ifndef NDEBUG
    if (nullptr == _view_model._engine_runtime_ptr->getOpenedProject()) {
        onOpenProjectCb(DEBUG_PATH "/example_proj");
        return;
    }
#else
    if (nullptr == _engine_runtime->getOpenedProject()) { return; }
#endif

    ImGui::Begin("Editor Menu", nullptr, DOCK_SPACE_FLAGS);

    ImGuiID const dock_space_id = ImGui::GetID(DOCK_SPACE_NAME.data());

    ImGui::DockSpace(dock_space_id, ImVec2(0.0F, 0.0F));

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            menu_component.update();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    menu_component.processFileDialog();

    ImguiSurface::addWidget(WORLD_OBJ_COMPONENT_NAME.data(),
                            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                                    world_object_component.update));
    ImguiSurface::addWidget(
            RENDER_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component.update),
            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar);
    ImguiSurface::addWidget(
            DETAILS_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component.update));
    ImguiSurface::addWidget(
            FILE_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component.update));
    ImguiSurface::addWidget(
            STATUS_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component.update));
    ImguiSurface::addWidget(
            USEFUL_OBJ_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(useful_obj_component.update));
}

bool MainWindow::isCursorInRenderComponent() const {
    spdlog::debug("Mouse pos: {}, {}", _context_ptr->_input_state->mouse_x,
                  _context_ptr->_input_state->mouse_y);
    spdlog::debug("Render rect: {}, {}, {}, {}",
                  render_component._render_rect.Min.x,
                  render_component._render_rect.Min.y,
                  render_component._render_rect.Max.x,
                  render_component._render_rect.Max.y);
    return render_component._render_rect.Contains(
            ImVec2{_context_ptr->_input_state->mouse_x,
                   _context_ptr->_input_state->mouse_y});
}

void MainWindow::update() {
    preUpdate();
    ImguiSurface::update();
}

void MainWindow::destroy() {
    ImguiSurface::destroy();
    _context_ptr->destroy();
}

void MainWindow::initWithEngineRuntime(Engine *engine_runtime_ptr) {
    _view_model._engine_runtime_ptr = engine_runtime_ptr;
    _view_model._renderer           = engine_runtime_ptr->getRenderer();

    ImguiSurface::init(_context_ptr->_window);
    _view_model._framebuffer = _view_model._renderer->getRenderFramebuffer();
}

MainWindow::MainWindow(WindowContext *const context_ptr)
    : _context_ptr(context_ptr) {
    this->menu_component.bindCallbacks(
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onNewProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onOpenProjectCb),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(onSaveProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onSaveAsProjectCb));
}

// for callbacks
void MainWindow::onNewProjectCb(std::string_view const &path) {}

void MainWindow::onOpenProjectCb(std::string_view const &path) {
    _view_model._engine_runtime_ptr->loadProject(path);
    _view_model._project_path = path;
}

void MainWindow::onSaveProjectCb() {}

void MainWindow::onSaveAsProjectCb(std::string_view const &path) {}

}// namespace taixu::editor