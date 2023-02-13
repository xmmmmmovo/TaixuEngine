//
// Created by xmmmmmovo on 2023/2/13.
//

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include "imgui_surface.hpp"

#include "core/base/macro.hpp"

namespace taixu::gui {
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(core::OPENGL_VERSION.data());
}
void ImguiSurface::create_layout() {}
void ImguiSurface::update() {}
void ImguiSurface::destroy() {}
}// namespace taixu::gui
