//
// Created by xmmmmmovo on 2023/2/13.
//

#include "imgui_surface.hpp"

#include "IconsFontAwesome6.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/base/macro.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace taixu::editor {

void ImguiSurface::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    auto font = io.Fonts->AddFontFromFileTTF(
            "res/fonts/SourceHanSansCN-Bold.otf", 18.0f, nullptr,
            io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.FontDefault = font;

    // merge in icons from Font Awesome
    static const ImWchar kIconsRanges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig         icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", 16.0f,
                                 &icons_config, kIconsRanges);
    // use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid

    io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
    io.ConfigFlags |=
            ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    // cherry colors, 3 intensities
#define HI(v) ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED(v) ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW(v) ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds
#define BG(v) ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

    auto &style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Tab]          = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    style.Colors[ImGuiCol_TabHovered]   = ImVec4{0.38f, 0.38f, 0.38f, 1.0f};
    style.Colors[ImGuiCol_TabActive]    = ImVec4{0.28f, 0.28f, 0.28f, 1.0f};
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};

    style.Colors[ImGuiCol_Text]           = TEXT(0.78f);
    style.Colors[ImGuiCol_TextDisabled]   = TEXT(0.28f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]        = BG(0.58f);
    style.Colors[ImGuiCol_PopupBg]        = BG(0.9f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = BG(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
    style.Colors[ImGuiCol_FrameBgActive]  = MED(1.00f);
    style.Colors[ImGuiCol_TitleBg]        = LOW(1.00f);
    style.Colors[ImGuiCol_TitleBgActive]  = HI(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
    style.Colors[ImGuiCol_MenuBarBg]        = BG(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]      = BG(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = MED(1.00f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] =
            ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
    style.Colors[ImGuiCol_ButtonActive]  = MED(1.00f);
    style.Colors[ImGuiCol_Header]        = MED(0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
    style.Colors[ImGuiCol_HeaderActive]  = HI(1.00f);
    style.Colors[ImGuiCol_Separator]     = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = MED(0.78f);
    style.Colors[ImGuiCol_SeparatorActive]  = MED(1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = MED(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]     = MED(1.00f);
    style.Colors[ImGuiCol_PlotLines]            = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]     = MED(1.00f);
    style.Colors[ImGuiCol_PlotHistogram]        = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]       = MED(0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg]     = BG(0.73f);

    style.WindowPadding     = ImVec2(6, 4);
    style.WindowRounding    = 0.0f;
    style.FramePadding      = ImVec2(5, 2);
    style.FrameRounding     = 3.0f;
    style.ItemSpacing       = ImVec2(7, 1);
    style.ItemInnerSpacing  = ImVec2(1, 1);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing     = 6.0f;
    style.ScrollbarSize     = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize       = 20.0f;
    style.GrabRounding      = 2.0f;

    style.WindowTitleAlign.x = 0.50f;

    style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
    style.FrameBorderSize         = 0.0f;

    style.WindowRounding   = 0.0f;
    style.WindowBorderSize = 0.0f;
    style.WindowPadding    = ImVec2(0.0f, 0.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(OPENGL_VERSION);
}

void ImguiSurface::preUpdate() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
}

void ImguiSurface::addWidget(const char                  *name,
                             std::function<void()> const &update,
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

    ImGuiIO const &io = ImGui::GetIO();

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
