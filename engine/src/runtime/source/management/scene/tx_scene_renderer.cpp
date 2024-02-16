//
// Created by xmmmmmovo on 1/7/2024.
//

#include "tx_scene_renderer.hpp"

#include "common/log/logger.hpp"

#include <IconsFontAwesome6.h>
#include <backends/imgui_impl_glfw.h>

namespace taixu {

void AbstractSceneRenderer::update(float delta_time, Scene* scene) {
    if (_enable_imgui) { imguiPreUpdate(); }
    updateScene(delta_time, scene);
    if (_enable_imgui) { imguiUpdate(); }
    presentToWindow();
}

void AbstractSceneRenderer::loadCNFont() const {
    _io->Fonts->AddFontDefault();

    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    const auto font = _io->Fonts->AddFontFromFileTTF(
            "res/fonts/SourceHanSansCN-Bold.otf", 18.0f, nullptr,
            _io->Fonts->GetGlyphRangesChineseSimplifiedCommon());
    _io->FontDefault = font;

    // merge in icons from Font Awesome
    static constexpr std::array<ImWchar, 3> K_ICONS_RANGES{ICON_MIN_FA,
                                                           ICON_MAX_16_FA, 0};
    static constexpr float                  FONT_SIZE{16.0f};
    ImFontConfig                            icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    _io->Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", FONT_SIZE,
                                   &icons_config, K_ICONS_RANGES.data());
}

void AbstractSceneRenderer::loadStyle() {
    ImGui::StyleColorsDark();

    // cherry colors, 3 intensities
#define HI_COL(v) ImVec4(0.502f, 0.075f, 0.256f, v)
#define MED_COL(v) ImVec4(0.455f, 0.198f, 0.301f, v)
#define LOW_COL(v) ImVec4(0.232f, 0.201f, 0.271f, v)
// backgrounds
#define BG_COL(v) ImVec4(0.200f, 0.220f, 0.270f, v)
// text
#define TEXT_COL(v) ImVec4(0.860f, 0.930f, 0.890f, v)

    _style = &ImGui::GetStyle();

    // NOLINTBEGIN
    _style->Colors[ImGuiCol_Tab]          = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    _style->Colors[ImGuiCol_TabHovered]   = ImVec4{0.38f, 0.38f, 0.38f, 1.0f};
    _style->Colors[ImGuiCol_TabActive]    = ImVec4{0.28f, 0.28f, 0.28f, 1.0f};
    _style->Colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
    _style->Colors[ImGuiCol_TabUnfocusedActive] =
            ImVec4{0.2f, 0.2f, 0.2f, 1.0f};

    _style->Colors[ImGuiCol_Text]         = TEXT_COL(0.78f);
    _style->Colors[ImGuiCol_TextDisabled] = TEXT_COL(0.28f);
    _style->Colors[ImGuiCol_WindowBg]     = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    _style->Colors[ImGuiCol_ChildBg]      = BG_COL(0.58f);
    _style->Colors[ImGuiCol_PopupBg]      = BG_COL(0.9f);
    _style->Colors[ImGuiCol_Border]       = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    _style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    _style->Colors[ImGuiCol_FrameBg]      = BG_COL(1.00f);
    _style->Colors[ImGuiCol_FrameBgHovered]   = MED_COL(0.78f);
    _style->Colors[ImGuiCol_FrameBgActive]    = MED_COL(1.00f);
    _style->Colors[ImGuiCol_TitleBg]          = LOW_COL(1.00f);
    _style->Colors[ImGuiCol_TitleBgActive]    = HI_COL(1.00f);
    _style->Colors[ImGuiCol_TitleBgCollapsed] = BG_COL(0.75f);
    _style->Colors[ImGuiCol_MenuBarBg]        = BG_COL(0.47f);
    _style->Colors[ImGuiCol_ScrollbarBg]      = BG_COL(1.00f);
    _style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    _style->Colors[ImGuiCol_ScrollbarGrabHovered] = MED_COL(0.78f);
    _style->Colors[ImGuiCol_ScrollbarGrabActive]  = MED_COL(1.00f);
    _style->Colors[ImGuiCol_CheckMark]  = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    _style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    _style->Colors[ImGuiCol_SliderGrabActive] =
            ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    _style->Colors[ImGuiCol_Button]        = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    _style->Colors[ImGuiCol_ButtonHovered] = MED_COL(0.86f);
    _style->Colors[ImGuiCol_ButtonActive]  = MED_COL(1.00f);
    _style->Colors[ImGuiCol_Header]        = MED_COL(0.76f);
    _style->Colors[ImGuiCol_HeaderHovered] = MED_COL(0.86f);
    _style->Colors[ImGuiCol_HeaderActive]  = HI_COL(1.00f);
    _style->Colors[ImGuiCol_Separator]     = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    _style->Colors[ImGuiCol_SeparatorHovered] = MED_COL(0.78f);
    _style->Colors[ImGuiCol_SeparatorActive]  = MED_COL(1.00f);
    _style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    _style->Colors[ImGuiCol_ResizeGripHovered]    = MED_COL(0.78f);
    _style->Colors[ImGuiCol_ResizeGripActive]     = MED_COL(1.00f);
    _style->Colors[ImGuiCol_PlotLines]            = TEXT_COL(0.63f);
    _style->Colors[ImGuiCol_PlotLinesHovered]     = MED_COL(1.00f);
    _style->Colors[ImGuiCol_PlotHistogram]        = TEXT_COL(0.63f);
    _style->Colors[ImGuiCol_PlotHistogramHovered] = MED_COL(1.00f);
    _style->Colors[ImGuiCol_TextSelectedBg]       = MED_COL(0.43f);
    _style->Colors[ImGuiCol_ModalWindowDimBg]     = BG_COL(0.73f);

    _style->WindowPadding     = ImVec2(6, 4);
    _style->WindowRounding    = 0.0f;
    _style->FramePadding      = ImVec2(5, 2);
    _style->FrameRounding     = 3.0f;
    _style->ItemSpacing       = ImVec2(7, 1);
    _style->ItemInnerSpacing  = ImVec2(1, 1);
    _style->TouchExtraPadding = ImVec2(0, 0);
    _style->IndentSpacing     = 6.0f;
    _style->ScrollbarSize     = 12.0f;
    _style->ScrollbarRounding = 16.0f;
    _style->GrabMinSize       = 20.0f;
    _style->GrabRounding      = 2.0f;

    _style->WindowTitleAlign.x = 0.50f;

    _style->Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
    _style->FrameBorderSize         = 0.0f;

    _style->WindowRounding   = 0.0f;
    _style->WindowBorderSize = 0.0f;
    _style->WindowPadding    = ImVec2(0.0f, 0.0f);
    // NOLINTEND
}

void AbstractSceneRenderer::initImguiForWindow(const Window* window) {
    ImGui_ImplGlfw_InitForOther(window->getRawWindow(), true);
}

void AbstractSceneRenderer::initAllForImgui(const Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    _io = &ImGui::GetIO();

    _io->ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
    // Gamepad Controls
    _io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
    _io->ConfigFlags |=
            ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport
    // Platform Windows

    loadCNFont();
    loadStyle();

    initImguiForWindow(window);
    initImguiForGraphicsAPI();
}

void AbstractSceneRenderer::imguiPreUpdate() {
    imguiGraphicsPreUpdate();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // TODO: 转移到组件中
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    static bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    {
        static float f       = 0.0f;
        static int   counter = 0;

        ImGui::Begin("Hello, world!");// Create a window called "Hello, world!"
                                      // and append into it.

        ImGui::Text("This is some useful text.");// Display some text (you can
                                                 // use a format strings too)
        ImGui::Checkbox("Demo Window",
                        &show_demo_window);// Edit bools storing our window
                                           // open/close state

        ImGui::SliderFloat(
                "float", &f, 0.0f,
                1.0f);// Edit 1 float using a slider from 0.0f to 1.0f

        if (ImGui::Button("Button")) counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / _io->Framerate, _io->Framerate);
        ImGui::End();
    }


    for (const auto& [name, update_func, flags, open] : _components) {
        // render the components
        if (!ImGui::Begin(name.data(), open, flags)) {
            ImGui::End();
            return;
        }
        update_func();
        ImGui::End();
    }
}

void AbstractSceneRenderer::imguiUpdate() {
    ImGui::Render();
    imguiGraphicsUpdate();
    if (_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void AbstractSceneRenderer::imguiDestroy() {
    imguiGraphicsDestroy();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void AbstractSceneRenderer::addComponent(
        const ImguiComponent& imgui_component) {
    _components.emplace_back(imgui_component);
}

}// namespace taixu
