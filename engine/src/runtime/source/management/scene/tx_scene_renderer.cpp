//
// Created by xmmmmmovo on 1/7/2024.
//

#include "tx_scene_renderer.hpp"

#include "common/log/logger.hpp"
#include "common/math/literal.hpp"

#include "gameplay/gui/fonts/fa_solid_900_iconfont.hpp"
#include "gameplay/gui/fonts/source_han_sans_cn_font.hpp"

#include <IconsFontAwesome6.h>
#include <backends/imgui_impl_glfw.h>


namespace taixu {

using namespace literal;

static constexpr ImguiStyleGroup DEFAULT_GROUP{
        Color{34_uc, 35, 42_uc, 255_uc},
        Color{42_uc, 44_uc, 54_uc, 255_uc},
        Color{230_uc, 175_uc, 137_uc, 255_uc},
        Color{97_uc, 97_uc, 106_uc, 255_uc},
        Color{47_uc, 179_uc, 135_uc, 255_uc},
        Color{76_uc, 148_uc, 123_uc, 255_uc},
        Color{76_uc, 48_uc, 67_uc, 255_uc},
        Color{105_uc, 50_uc, 68_uc, 255_uc},
        Color{0_uc, 0_uc, 0_uc, 255_uc}};

void AbstractSceneRenderer::update(float delta_time, Scene* scene) {
    updateScene(delta_time, scene);
    if (_enable_imgui) { imguiPreUpdate(); }
    if (_enable_imgui) { imguiUpdate(); }
    presentToWindow();
}

void AbstractSceneRenderer::loadFont() const {
    _io->Fonts->AddFontDefault();

    static constexpr float FONT_SIZE{18.0f};
    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    const auto             font = _io->Fonts->AddFontFromMemoryCompressedTTF(
            source_han_sans_cn_font_compressed_data,
            source_han_sans_cn_font_compressed_size, FONT_SIZE, nullptr,
            // 这里包括了Latin范围
            _io->Fonts->GetGlyphRangesChineseSimplifiedCommon());
    _io->FontDefault = font;

    // merge in icons from Font Awesome
    static constexpr std::array<ImWchar, 3> K_ICONS_RANGES{ICON_MIN_FA,
                                                           ICON_MAX_16_FA, 0};
    static constexpr float                  ICONFONT_SIZE{16.0f};
    ImFontConfig                            icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    _io->Fonts->AddFontFromMemoryCompressedBase85TTF(
            fa_solid_900_iconfont_compressed_data_base85, ICONFONT_SIZE,
            &icons_config, K_ICONS_RANGES.data());
}

void AbstractSceneRenderer::loadStyle() {
    ImGui::StyleColorsDark();

    _style = &ImGui::GetStyle();

    _style->WindowBorderSize         = 1.0f;
    _style->WindowRounding           = 8.0f;
    _style->PopupRounding            = 8.0f;
    _style->TabRounding              = 8.0;
    _style->FrameRounding            = 8.0;
    _style->GrabRounding             = 4.0;
    _style->WindowPadding            = {5.0f, 5.0f};
    _style->ItemSpacing              = {4.0f, 4.0f};
    _style->ItemInnerSpacing         = {3.0f, 3.0f};
    _style->WindowMenuButtonPosition = 0;
    _style->WindowTitleAlign         = {0.5f, 0.5f};
    _style->GrabMinSize              = 6.5f;
    _style->ScrollbarSize            = 12.0f;
    _style->FramePadding             = {4.0f, 4.0f};
    _style->FrameBorderSize          = 1.0f;
    _style->HoverStationaryDelay     = 0.35f;
    _style->HoverDelayNormal         = 0.5f;
    _style->HoverDelayShort          = 0.25f;
    _style->SeparatorTextAlign       = {0.0f, 0.5f};
    _style->SeparatorTextBorderSize  = 1.0f;
    _style->SeparatorTextPadding     = {20.0f, 10.0f};

    constexpr ImVec4 BG      = DEFAULT_GROUP.background.toImVec4();
    constexpr ImVec4 FG      = DEFAULT_GROUP.foreground.toImVec4();
    constexpr ImVec4 TEXT    = DEFAULT_GROUP.text.toImVec4();
    constexpr ImVec4 TEXT_BG = DEFAULT_GROUP.text_background.toImVec4();
    constexpr ImVec4 HIGHLIGHT_PRIMARY =
            DEFAULT_GROUP.highlight_primary.toImVec4();
    constexpr ImVec4 HOVER_PRIMARY = DEFAULT_GROUP.hover_primary.toImVec4();
    constexpr ImVec4 HIGHLIGHT_SECONDARY =
            DEFAULT_GROUP.highlight_secondary.toImVec4();
    constexpr ImVec4 HOVER_SECONDARY = DEFAULT_GROUP.hover_secondary.toImVec4();
    constexpr ImVec4 MODAL_DIM       = DEFAULT_GROUP.modal_dim.toImVec4();

    _style->Colors[ImGuiCol_WindowBg]             = BG;
    _style->Colors[ImGuiCol_Border]               = FG;
    _style->Colors[ImGuiCol_MenuBarBg]            = FG;
    _style->Colors[ImGuiCol_Separator]            = TEXT_BG;
    _style->Colors[ImGuiCol_TitleBg]              = FG;
    _style->Colors[ImGuiCol_TitleBgActive]        = FG;
    _style->Colors[ImGuiCol_Tab]                  = FG;
    _style->Colors[ImGuiCol_TabUnfocused]         = FG;
    _style->Colors[ImGuiCol_TabUnfocusedActive]   = FG;
    _style->Colors[ImGuiCol_TabActive]            = FG;
    _style->Colors[ImGuiCol_TabHovered]           = FG;
    _style->Colors[ImGuiCol_PopupBg]              = BG;
    _style->Colors[ImGuiCol_FrameBg]              = BG;
    _style->Colors[ImGuiCol_FrameBgHovered]       = BG;
    _style->Colors[ImGuiCol_Text]                 = TEXT;
    _style->Colors[ImGuiCol_ResizeGrip]           = HIGHLIGHT_PRIMARY;
    _style->Colors[ImGuiCol_ScrollbarGrabActive]  = HIGHLIGHT_PRIMARY;
    _style->Colors[ImGuiCol_ScrollbarGrabHovered] = HOVER_PRIMARY;
    _style->Colors[ImGuiCol_ScrollbarBg]          = BG;
    _style->Colors[ImGuiCol_ScrollbarGrab]        = FG;
    _style->Colors[ImGuiCol_Header]               = HIGHLIGHT_SECONDARY;
    _style->Colors[ImGuiCol_HeaderHovered]        = HOVER_SECONDARY;
    _style->Colors[ImGuiCol_HeaderActive]         = HIGHLIGHT_SECONDARY;
    _style->Colors[ImGuiCol_Button]               = FG;
    _style->Colors[ImGuiCol_ButtonHovered]        = HOVER_SECONDARY;
    _style->Colors[ImGuiCol_ButtonActive]         = HIGHLIGHT_SECONDARY;
    _style->Colors[ImGuiCol_ModalWindowDimBg]     = MODAL_DIM;
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
    _io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
    _io->ConfigFlags |=
            ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport
    // Platform Windows

    loadFont();
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