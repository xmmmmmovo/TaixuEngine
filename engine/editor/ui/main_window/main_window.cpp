//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"
#include <spdlog/spdlog.h>

#include "core/base/path.hpp"
#include "gameplay/gui/imgui_surface.hpp"

#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
#include "GraphEditor.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"

namespace taixu::editor {
void MainWindow::init() {
    spdlog::info("Main window init start!");

    _context_ptr->registerOnMouseButtonFn(
            [this](int button, int action, int /*mods*/) {
                if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
                    if (_context_ptr->_cam_mode) {
                        _context_ptr->_cam_mode = false;
                        glfwSetInputMode(_context_ptr->_window, GLFW_CURSOR,
                                         GLFW_CURSOR_NORMAL);
                    } else {
                        if (isCursorInRenderComponent()) {
                            _context_ptr->_cam_mode = true;
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
    if (nullptr == _engine_runtime->getOpenedProject()) {
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
    spdlog::debug("Mouse pos: {}, {}", _context_ptr->_mouse_pos.x,
                  _context_ptr->_mouse_pos.y);
    spdlog::debug("Render rect: {}, {}, {}, {}",
                  render_component->_render_rect.Min.x,
                  render_component->_render_rect.Min.y,
                  render_component->_render_rect.Max.x,
                  render_component->_render_rect.Max.y);
    return render_component->_render_rect.Contains(_context_ptr->_mouse_pos);
}

void MainWindow::operationLisen() {
    //if(isCursorInRenderComponent())
    //{
        //ImGui::NewFrame();
        //ImGuizmo::BeginFrame();
        auto gizmoWindowFlags = detail_component->gizmoWindowFlags;
        ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImGuizmo::SetDrawlist(drawList);
        ImVec2 endpoint = ImGui::GetWindowPos();
        endpoint = ImVec2(endpoint.x+windowWidth, endpoint.y+windowHeight);
        drawList->AddRect(ImGui::GetWindowPos(),  endpoint, IM_COL32_WHITE);
        
        ImGui::End();
        
        //ImGui::EndFrame();
        //ImGuiWindow* window = ImGui::GetCurrentWindow();
        //gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;
        // for(auto const &entity : _detail_category->entities())
        // {
        //     ImGuizmo::SetID(entity);

        //     auto trans = _current_scene->ecs_coordinator
        //                         .getComponent<TransformComponent>(entity);
        //     float* mat = glm::value_ptr(trans.transform);
        //     detail_component->transformLisen(_current_scene->_camera.get(),mat , lastUsing==entity);
        //     if (ImGuizmo::IsUsing())
        //     {
        //         lastUsing = entity;
        //     }
        // }
    //}
    
       
}

void MainWindow::update() {
    preUpdate();
    //operationLisen();
    ImguiSurface::update();
}

void MainWindow::destroy() {
    ImguiSurface::destroy();
    _context_ptr->destroy();
}

void MainWindow::initWithEngineRuntime(Engine *engine_runtime_ptr) {
    this->_engine_runtime = engine_runtime_ptr;
    this->_renderer       = engine_runtime_ptr->getRenderer();

    ImguiSurface::init(_context_ptr->_window);
    render_component->_framebuffer = _renderer->getRenderFramebuffer();
}

void MainWindow::bindScene(Scene *scene) {
    _current_scene = scene;
    if (_current_scene != nullptr) {
            auto &coordinator = _current_scene->ecs_coordinator;
            _detail_system =
                    coordinator.registerSystem(_detail_system_id);
            {
                Signature trans_signature;
                trans_signature.set(
                        coordinator.getComponentType<TransformComponent>());
                coordinator.setsystemSignature(_detail_system_id,
                                                 trans_signature);
            }

        } else {
            _detail_system = nullptr;
        }
    
}

MainWindow::MainWindow(WindowContext *const context_ptr)
    : _context_ptr(context_ptr) {
    this->menu_component->bindCallbacks(
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onNewProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onOpenProjectCb),
            INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(onSaveProjectCb),
            INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onSaveAsProjectCb));
}

// for callbacks
void MainWindow::onNewProjectCb(std::string_view const &path) {}

void MainWindow::onOpenProjectCb(std::string_view const &path) {
    this->_engine_runtime->loadProject(path);
}

void MainWindow::onSaveProjectCb() {}

void MainWindow::onSaveAsProjectCb(std::string_view const &path) {}

}// namespace taixu::editor