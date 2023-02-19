//
// Created by xmmmmmovo on 2023/2/13.
//

#include "imgui_surface.hpp"

#include <IconsFontAwesome6.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>

#include "core/base/macro.hpp"
#include "core/utils/function_utils.hpp"

namespace taixu::editor {
void ImguiSurface::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    auto font = io.Fonts->AddFontFromFileTTF(
            "res/fonts/SourceHanSansCN-Bold.otf", 16.0f, nullptr,
            io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.FontDefault = font;

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig         icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", 16.0f,
                                 &icons_config, icons_ranges);
    // use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid

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
    ImGui_ImplOpenGL3_Init(core::OPENGL_VERSION);

    menu_component->init();

    render_component->init();
    world_object_component->init();
    detail_component->init();
    file_component->init();
    status_component->init();
    useful_obj_component->init();

    tool_bar_component->init();
}

void ImguiSurface::preUpdate() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Create the docking environment
    ImGuiWindowFlags window_flags =
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

    ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f));

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            menu_component->update();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
    addWidget(WORLD_OBJ_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                      world_object_component->update));
    addWidget(RENDER_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(render_component->update));
    addWidget(DETAILS_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(detail_component->update));
    addWidget(FILE_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(file_component->update));
    addWidget(STATUS_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(status_component->update));
    addWidget(USEFUL_OBJ_COMPONENT_NAME, INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(
                                                 useful_obj_component->update));
    addWidget(TOOLBAR_COMPONENT_NAME,
              INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(tool_bar_component->update),
              ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar |
                      ImGuiWindowFlags_NoScrollWithMouse);
}

void ImguiSurface::addWidget(const char                  *name,
                             const std::function<void()> &update,
                             ImGuiWindowFlags const flags, bool *open) {
    if (!ImGui::Begin(name, open, flags)) {
        ImGui::End();
        return;
    }
    update();
    ImGui::End();
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
