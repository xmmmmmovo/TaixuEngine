//
// Created by xmmmmmovo on 2023/2/12.
//
#include "main_window.hpp"
#include <imgui.h>

#include <GraphEditor.h>
#include <gameplay/gui/imgui_surface.hpp>
#include <platform/glfw/window.hpp>
#include <platform/os/path.hpp>
#include <utility>

namespace taixu::editor {

void MainWindow::buildUpUsefulObjHierarchy() {
    _view_model.useful_objs_hierarchy = {
            {
                    .name = "Objects",
                    .data = "",
                    .children =
                            {
                                    {
                                            .name     = "Cube",
                                            .children = {},
                                    },
                                    {
                                            .name     = "Sphere",
                                            .children = {},
                                    },
                            },
            },
            {.name     = "Lights",
             .data     = "",
             .children = {{
                                  .name     = "PointLight",
                                  .children = {},
                          },
                          {
                                  .name     = "DirectionalLight",
                                  .children = {},
                          }}}};
}

void MainWindow::buildUpPathHierarchy() {
    _view_model.selected_path = "";
    _view_model.selected_node = nullptr;

    _view_model.path_hierarchy.clear();
    for (auto& directory_entry :
         std::filesystem::directory_iterator(_view_model.project_path)) {
        const auto& path = directory_entry.path();
        if (path.filename() == ".git" || path.filename() == ".gitignore") {
            continue;
        }
        if (directory_entry.is_directory()) {
            _view_model.path_hierarchy.push_back(
                    {.name = path.filename().generic_string(),
                     .data = getRelativePath(_view_model.project_path, path),
                     .children = {}});
        }
    }
}

void MainWindow::init(const std::vector<std::string>& args) {
    _engine_runtime_ptr = &Engine::getInstance();
    _engine_runtime_ptr->init(args);

    _view_model.init(_engine_runtime_ptr);

    INFO_LOG("Main window init start!");
    RenderAPI const api =
            _engine_runtime_ptr->context().engine_args->render_api();

    _window_ptr = WindowFactory::createWindow(api);
    _window_ptr->init(_window_title, _width, _height);
    _window_ptr->showWindow();
    //    _window_ptr->registerOnMouseButtonFn(
    //            [this](int button, int action, int /*mods*/) {
    //                if (button == GLFW_MOUSE_BUTTON_RIGHT && action ==
    //                GLFW_PRESS) {
    //                    if (_view_model.renderer->move_mode()) {
    //                        _view_model.renderer->set_move_mode(false);
    //                        glfwSetInputMode(_window_ptr->_window,
    //                        GLFW_CURSOR,
    //                                         GLFW_CURSOR_NORMAL);
    //                    } else {
    //                        if (isCursorInRenderComponent()) {
    //                            _view_model.renderer->set_move_mode(true);
    //                            glfwSetInputMode(_window_ptr->_window,
    //                            GLFW_CURSOR,
    //                                             GLFW_CURSOR_DISABLED);
    //                        }
    //                    }
    //                }
    //            });

    buildUpUsefulObjHierarchy();

    //    INFO_LOG("Main window init finished!");
}

void MainWindow::preUpdate() {
    ImguiLayers::preUpdate();

    //    if (nullptr == _view_model.engine_runtime_ptr->getOpenedProject()) {
    //        return;
    //    }

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

    //    menu_component.processFileDialog();
    //
    //    ImguiSurface::addWidget(WORLD_OBJ_COMPONENT_NAME.data(),
    //                            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
    //                                    world_object_component.update));
    //    ImguiSurface::addWidget(
    //            RENDER_COMPONENT_NAME.data(),
    //            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component.update),
    //            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar);
    //    ImguiSurface::addWidget(
    //            DETAILS_COMPONENT_NAME.data(),
    //            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component.update));
    //    ImguiSurface::addWidget(
    //            FILE_COMPONENT_NAME.data(),
    //            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component.update));
    //    ImguiSurface::addWidget(
    //            STATUS_COMPONENT_NAME.data(),
    //            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component.update));
    //    ImguiSurface::addWidget(
    //            USEFUL_OBJ_COMPONENT_NAME.data(),
    //            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(useful_obj_component.update));
}

bool MainWindow::isCursorInRenderComponent() const {
    //    spdlog::debug("Mouse pos: {}, {}", _window_ptr->_input_state->mouse_x,
    //                  _window_ptr->_input_state->mouse_y);
    //    spdlog::debug("Render rect: {}, {}, {}, {}",
    //                  render_component._render_rect.Min.x,
    //                  render_component._render_rect.Min.y,
    //                  render_component._render_rect.Max.x,
    //                  render_component._render_rect.Max.y);
    //    return render_component._render_rect.Contains(
    //            ImVec2{_window_ptr->_input_state->mouse_x,
    //                   _window_ptr->_input_state->mouse_y});
    return true;
}

void MainWindow::update() {
    preUpdate();
    ImguiLayers::update();
}

void MainWindow::show() const {
    _engine_runtime_ptr->start();
    while (!_window_ptr->shouldClose()) {
        _engine_runtime_ptr->update();
        _window_ptr->handleEvents();
    }
}

void MainWindow::destroy() const {
    ImguiLayers::destroy();
    _window_ptr->destroy();
}

MainWindow::MainWindow(std::string title, int32_t width, int32_t height)
    : _window_title(std::move(title)), _width(width), _height(height) {
    this->_window_ptr, this->menu_component.bindCallbacks(
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onNewProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onOpenProjectCb),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(onSaveProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onSaveAsProjectCb));
}

// for callbacks
void MainWindow::onNewProjectCb(std::string_view const& path) {}

void MainWindow::onOpenProjectCb(std::string_view const& path) {
    //    _view_model.engine_runtime_ptr->loadProject(path);
    _view_model.project_path = path;
    buildUpPathHierarchy();
}

void MainWindow::onSaveProjectCb() {}

void MainWindow::onSaveAsProjectCb(std::string_view const& path) {}

}// namespace taixu::editor