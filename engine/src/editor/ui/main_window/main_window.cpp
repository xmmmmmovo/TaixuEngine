//
// Created by xmmmmmovo on 2023/2/12.
//
#include "main_window.hpp"

#include "imgui.h"

#include "taixu/engine/engine.hpp"
#include "taixu/gameplay/gui/window_factory.hpp"

#include "ui/common/dialog_helper.hpp"
#include "ui/common/editor_context.hpp"

#include <utility>

namespace taixu::editor {

void MainWindow::buildUpPathHierarchy() {
    // _view_model.selected_path = "";
    // _view_model.selected_node = nullptr;
    //
    // _view_model.path_hierarchy.clear();
    // for (auto& directory_entry :
    //      std::filesystem::directory_iterator(_view_model.project_path)) {
    //     const auto& path = directory_entry.path();
    //     if (path.filename() == ".git" || path.filename() == ".gitignore") {
    //         continue;
    //     }
    //     if (directory_entry.is_directory()) {
    //         _view_model.path_hierarchy.push_back(
    //                 {.name     = path.filename().generic_string(),
    //                  .children = {},
    //                  .data = getRelativePath(_view_model.project_path,
    //                  path)});
    //     }
    // }
}

void MainWindow::init() {

    _window_ptr->init();
    _window_ptr->showWindow();

    g_engine.initWithWindow(_window_ptr.get());

    g_engine.enableImgui([this] { this->imguiUpdate(); });

    registerCallback(Callbacks::FILE_OPEN_PROJECT, Handler{+[](std::string const& file_path, ViewModel& view_model) {
                         g_engine.loadProject(file_path);
                         auto& node         = view_model.file_component_hierarchy;
                         node.data.filepath = "";
                         node.data.filename = g_engine.getOpenedProject()->raw.project_path.filename().generic_string();
                         node.data.filetype = FileEntryType::DIRECTORY;
                         view_model.selected_node = &node;
                         recursiveLoadFileTree(node);
                     }});

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

    INFO_LOG("Main _window init finished!");
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
}

void MainWindow::imguiUpdate() {
    ImGui::Begin(VIEW_HOLDER_NAME.data(), nullptr, IMGUI_WINDOW_FLAG);
    _dock_space_id = ImGui::GetID(DOCK_SPACE_NAME.data());
    ImGui::DockSpace(_dock_space_id, ImVec2{0.0f, 0.0f}, IMGUI_DOCKSPACE_FLAGS);

    if (g_engine.getOpenedProject() == nullptr) {
        if (g_engine.getArgs().project_path().empty()) {
            openFileDialog(STARTUP_OPEN_PROJECT_DLG_KEY.data(), DIRECTORY_CONFIG);
            displayAndProcessFileDialog(STARTUP_OPEN_PROJECT_DLG_KEY.data(), _view_model, Callbacks::FILE_OPEN_PROJECT);
        } else {
            invokeCallback(Callbacks::FILE_OPEN_PROJECT, g_engine.getArgs().project_path(), _view_model);
        }
    } else {
        _menu_component.update();
        UsefulObjectComponent::update();
        _file_component.update();
        _scene_graph_component.update();
        _render_component.update();
        _detail_component.update();
    }

    ImGui::End();
}

void MainWindow::start() const {
    g_engine.beforeStart();
    while (!_window_ptr->shouldClose()) {
        g_engine.update();
        _window_ptr->handleEvents();
    }
}

void MainWindow::destroy() const {
    _window_ptr->destroy();
}

MainWindow::MainWindow(WindowInfo&& window_info)
    : _window_ptr(WindowFactory::createProduct(WindowAPI::GLFW, std::move(window_info))) {
}

}// namespace taixu::editor
