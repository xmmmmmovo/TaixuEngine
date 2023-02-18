//
// Created by xmmmmmovo on 2023/2/13.
//

#include "imgui_surface.hpp"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <spdlog/spdlog.h>

#include "core/base/macro.hpp"

namespace taixu::editor {
void ImguiSurface::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
    io.ConfigFlags |=
            ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    auto &colors              = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.1f, 1.0f};

    colors[ImGuiCol_Header]        = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
    colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_HeaderActive]  = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

    colors[ImGuiCol_Button]        = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
    colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_ButtonActive]  = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

    colors[ImGuiCol_FrameBg]        = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
    colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
    colors[ImGuiCol_FrameBgActive]  = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

    colors[ImGuiCol_Tab]                = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_TabHovered]         = ImVec4{0.38f, 0.38f, 0.38f, 1.0f};
    colors[ImGuiCol_TabActive]          = ImVec4{0.28f, 0.28f, 0.28f, 1.0f};
    colors[ImGuiCol_TabUnfocused]       = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};

    colors[ImGuiCol_TitleBg]          = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_TitleBgActive]    = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(core::OPENGL_VERSION.data());

    menu_component->init();
    world_object_component->init();
    render_component->init();
}

void ImguiSurface::preUpdate() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Create the docking environment
    ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_DockSpace;
    ImGuiWindowFlags   window_flags =
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
            ImGuiConfigFlags_NoMouseCursorChange |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("Editor Menu", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dock_space_id = ImGui::GetID(DOCK_SPACE_NAME);

    if (ImGui::DockBuilderGetNode(dock_space_id) == nullptr) {
        ImGui::DockBuilderRemoveNode(dock_space_id);

        ImGui::DockBuilderAddNode(dock_space_id, dock_flags);
        ImGui::DockBuilderSetNodePos(
                dock_space_id,
                ImVec2(viewport->WorkPos.x, viewport->WorkPos.y + 18.0f));
        //        ImGui::DockBuilderSetNodeSize(
        //                dock_space_id, ImVec2(m_io->m_width, m_io->m_height - 18.0f));

        ImGuiID center = dock_space_id;
        ImGuiID left;
        ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right,
                                                    0.25f, nullptr, &left);

        ImGuiID left_other;
        ImGuiID left_file_content = ImGui::DockBuilderSplitNode(
                left, ImGuiDir_Down, 0.30f, nullptr, &left_other);

        ImGuiID left_game_engine;
        ImGuiID left_asset = ImGui::DockBuilderSplitNode(
                left_other, ImGuiDir_Left, 0.30f, nullptr, &left_game_engine);

        ImGui::DockBuilderDockWindow(WORLD_OBJ_COMPONENT_NAME, left_asset);
        ImGui::DockBuilderDockWindow(DETAILS_COMPONENT_NAME, right);
        ImGui::DockBuilderDockWindow(FILE_COMPONENT_NAME, left_file_content);
        ImGui::DockBuilderDockWindow(RENDER_COMPONENT_NAME, left_game_engine);

        ImGui::DockBuilderFinish(dock_space_id);
    }

    ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f));

    menu_component->update();

    ImGui::End();

    world_object_component->update();
    render_component->update();
    detail_component->update();
    file_component->update();
}

void ImguiSurface::update() {
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImguiSurface::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
}// namespace taixu::editor
