//
// Created by xmmmmmovo on 2023/2/12.
//
#include "main_window.hpp"

#include "management/scene/tx_scene_renderer.hpp"
#include "ui/common/editor_context.hpp"

#include <imgui.h>

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

    _window_ptr->init();
    _window_ptr->showWindow();
    g_editor_context.engine_ptr->init(args, _window_ptr.get());

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

    g_editor_context.engine_ptr->renderer->addComponent(
            menu_component.getComponentInfo());

    INFO_LOG("Main window init finished!");
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

void MainWindow::update() {}

void MainWindow::start() const {
    g_editor_context.engine_ptr->beforeStart();
    while (!_window_ptr->shouldClose()) {
        g_editor_context.engine_ptr->update();
        _window_ptr->handleEvents();
    }
}

void MainWindow::destroy() const { _window_ptr->destroy(); }

MainWindow::MainWindow(WindowInfo&& window_info)
    : _window_ptr(
              std::make_unique<Window>(std::forward<WindowInfo>(window_info))) {
}

}// namespace taixu::editor