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

    context_ptr->registerOnScrollFn([this](double /*xoffset*/, double yoffset) {
        if (context_ptr->_state == EngineState::GAMEMODE) {
            context_ptr->_editor_camera->processMouseScroll(yoffset);
        }
    });

    context_ptr->registerOnCursorPosFn([this](double xpos, double ypos) {
        if (_last_mouse_pos.x == -1.0F && _last_mouse_pos.y == -1.0F) {
            _last_mouse_pos.x = xpos;
            _last_mouse_pos.y = ypos;
        }
        _mouse_pos.x = xpos;
        _mouse_pos.y = ypos;
        if (_cam_mode) {
            context_ptr->_editor_camera->processMouseMovement(
                    _mouse_pos.x - _last_mouse_pos.x,
                    _last_mouse_pos.y - _mouse_pos.y);
        }
        _last_mouse_pos = _mouse_pos;
    });

    context_ptr->registerOnMouseButtonFn(
            [this](int button, int action, int /*mods*/) {
                if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
                    if (_cam_mode) {
                        _cam_mode = false;
                        glfwSetInputMode(context_ptr->_window, GLFW_CURSOR,
                                         GLFW_CURSOR_NORMAL);
                    } else {
                        if (isCursorInRenderComponent()) {
                            _cam_mode = true;
                            glfwSetInputMode(context_ptr->_window, GLFW_CURSOR,
                                             GLFW_CURSOR_DISABLED);
                        }
                    }
                }
            });

    spdlog::info("Main window start finished!");
}

void MainWindow::preUpdate() {
    ImguiSurface::preUpdate();

//    if (nullptr == _engine_runtime->getOpenedProject()) { return; }

    ImGui::Begin("Editor Menu", nullptr, DOCK_SPACE_FLAGS);

    ImGuiID const dock_space_id = ImGui::GetID(DOCK_SPACE_NAME.data());

    ImGui::DockSpace(dock_space_id, ImVec2(0.0F, 0.0F));

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            menu_component->update();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();

    menu_component->processFileDialog();

    ImguiSurface::addWidget(WORLD_OBJ_COMPONENT_NAME.data(),
                            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                                    world_object_component->update));
    ImguiSurface::addWidget(
            RENDER_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component->update),
            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar);
    ImguiSurface::addWidget(
            DETAILS_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component->update));
    ImguiSurface::addWidget(
            FILE_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component->update));
    ImguiSurface::addWidget(
            STATUS_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component->update));
    ImguiSurface::addWidget(
            USEFUL_OBJ_COMPONENT_NAME.data(),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(useful_obj_component->update));
}

bool MainWindow::isCursorInRenderComponent() const {
    spdlog::debug("Mouse pos: {}, {}", _mouse_pos.x, _mouse_pos.y);
    spdlog::debug("Render rect: {}, {}, {}, {}",
                  render_component->_render_rect.Min.x,
                  render_component->_render_rect.Min.y,
                  render_component->_render_rect.Max.x,
                  render_component->_render_rect.Max.y);
    return render_component->_render_rect.Contains(_mouse_pos);
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
    this->_engine_runtime = engine_runtime_ptr;
    this->renderer        = engine_runtime_ptr->getRenderer();

    ImguiSurface::init(context_ptr->_window);
    render_component->_renderer = renderer;
    renderer->_camera           = context_ptr->_editor_camera.get();

    InputSystem::getInstance().registerEditorCallback([this](float delta_time) {
        if (glfwGetKey(context_ptr->_window, GLFW_KEY_W) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(
                    CameraMovement::FORWARD, delta_time);
        }
        if (glfwGetKey(context_ptr->_window, GLFW_KEY_S) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(
                    CameraMovement::BACKWARD, delta_time);
        }
        if (glfwGetKey(context_ptr->_window, GLFW_KEY_A) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(CameraMovement::LEFT,
                                                         delta_time);
        }
        if (glfwGetKey(context_ptr->_window, GLFW_KEY_D) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(CameraMovement::RIGHT,
                                                         delta_time);
        }

        if (glfwGetKey(context_ptr->_window, GLFW_KEY_E) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(CameraMovement::UP,
                                                         delta_time);
        }
        if (glfwGetKey(context_ptr->_window, GLFW_KEY_Q) == GLFW_PRESS) {
            context_ptr->_editor_camera->processKeyboard(CameraMovement::DOWN,
                                                         delta_time);
        }
    });
}

MainWindow::MainWindow(WindowContext* const context_ptr)
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
    this->_engine_runtime->loadProject(path);
}
void MainWindow::onSaveProjectCb() {}
void MainWindow::onSaveAsProjectCb(std::string_view const& path) {}


}// namespace taixu::editor