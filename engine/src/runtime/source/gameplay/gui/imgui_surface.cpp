//
// Created by xmmmmmovo on 2023/2/13.
//

#include "gameplay/gui/imgui_surface.hpp"

#include "IconsFontAwesome6.h"
#include "ImGuizmo.h"
#include "imgui.h"
#include "imgui_internal.h"

#include <common/base/macro.hpp>

namespace taixu::editor {

void ImguiLayers::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    auto font = io.Fonts->AddFontFromFileTTF(
            "res/fonts/SourceHanSansCN-Bold.otf", 18.0f, nullptr,
            io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.FontDefault = font;

    // merge in icons from Font Awesome
    static constexpr std::array<ImWchar, 3> K_ICONS_RANGES{ICON_MIN_FA,
                                                           ICON_MAX_16_FA, 0};
    static constexpr float                  FONT_SIZE{16.0f};
    ImFontConfig                            icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", FONT_SIZE,
                                 &icons_config, K_ICONS_RANGES.data());

    io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
    // Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport
                                                       // / Platform Windows

    ImGui::StyleColorsDark();

    // cherry colors, 3 intensities
#define HI_COL(v) ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED_COL(v) ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW_COL(v) ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds
#define BG_COL(v) ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT_COL(v) ImVec4(0.860f, 0.930f, 0.890f, v)

    auto& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Tab]          = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    style.Colors[ImGuiCol_TabHovered]   = ImVec4{0.38f, 0.38f, 0.38f, 1.0f};
    style.Colors[ImGuiCol_TabActive]    = ImVec4{0.28f, 0.28f, 0.28f, 1.0f};
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};

    style.Colors[ImGuiCol_Text]           = TEXT_COL(0.78f);
    style.Colors[ImGuiCol_TextDisabled]   = TEXT_COL(0.28f);
    style.Colors[ImGuiCol_WindowBg]       = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]        = BG_COL(0.58f);
    style.Colors[ImGuiCol_PopupBg]        = BG_COL(0.9f);
    style.Colors[ImGuiCol_Border]         = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow]   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]        = BG_COL(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = MED_COL(0.78f);
    style.Colors[ImGuiCol_FrameBgActive]  = MED_COL(1.00f);
    style.Colors[ImGuiCol_TitleBg]        = LOW_COL(1.00f);
    style.Colors[ImGuiCol_TitleBgActive]  = HI_COL(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = BG_COL(0.75f);
    style.Colors[ImGuiCol_MenuBarBg]        = BG_COL(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg]      = BG_COL(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED_COL(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]  = MED_COL(1.00f);
    style.Colors[ImGuiCol_CheckMark]  = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] =
            ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button]        = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = MED_COL(0.86f);
    style.Colors[ImGuiCol_ButtonActive]  = MED_COL(1.00f);
    style.Colors[ImGuiCol_Header]        = MED_COL(0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = MED_COL(0.86f);
    style.Colors[ImGuiCol_HeaderActive]  = HI_COL(1.00f);
    style.Colors[ImGuiCol_Separator]     = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = MED_COL(0.78f);
    style.Colors[ImGuiCol_SeparatorActive]  = MED_COL(1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered]    = MED_COL(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]     = MED_COL(1.00f);
    style.Colors[ImGuiCol_PlotLines]            = TEXT_COL(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]     = MED_COL(1.00f);
    style.Colors[ImGuiCol_PlotHistogram]        = TEXT_COL(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = MED_COL(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]       = MED_COL(0.43f);
    style.Colors[ImGuiCol_ModalWindowDimBg]     = BG_COL(0.73f);

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
}

void ImguiLayers::preUpdate() {
    // Start the Dear ImGui frame
    ImGui::NewFrame();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
}

void ImguiLayers::addWidget(const char*                  name,
                            std::function<void()> const& update,
                            ImGuiWindowFlags const flags, bool* open) {
    if (!ImGui::Begin(name, open, flags)) {
        ImGui::End();
        return;
    }
    update();
    ImGui::End();
}

void ImguiLayers::update() {
    // Rendering
    ImGui::Render();

    ImGuiIO const& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void ImguiLayers::destroy() { ImGui::DestroyContext(); }

}// namespace taixu::editor
