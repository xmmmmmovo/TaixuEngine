//
// Created by xmmmmmovo on 1/7/2024.
//
#include "management/scene/tx_scene_renderer.hpp"

#include "common/math/math.hpp"
#include "gameplay/gui/glfw_window.hpp"
#include "management/gfx/tx_context.hpp"
#include "taixu/common/base/result.hpp"
#include "taixu/common/log/logger.hpp"
#include "taixu/engine/engine.hpp"
#include "taixu/gameplay/gui/window.hpp"

#include "generated/fonts/lucide_iconfont.hpp"
#include "generated/fonts/source_han_sans_cn_font.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "imgui.h"
#include "imgui/icons/IconsLucide.h"

namespace taixu {

using namespace literals;

static constexpr ImguiStyleGroup DEFAULT_STYLE_GROUP{
        Color{34_uc, 35, 42_uc, 255_uc},       Color{42_uc, 44_uc, 54_uc, 255_uc},
        Color{230_uc, 175_uc, 137_uc, 255_uc}, Color{97_uc, 97_uc, 106_uc, 255_uc},
        Color{47_uc, 179_uc, 135_uc, 255_uc},  Color{76_uc, 148_uc, 123_uc, 255_uc},
        Color{76_uc, 48_uc, 67_uc, 255_uc},    Color{105_uc, 50_uc, 68_uc, 255_uc},
        Color{0_uc, 0_uc, 0_uc, 255_uc}};

void TXSceneRenderer::init(Window* window) {
    initForGraphicsAPI(window);
    initImgui(window);
}

void TXSceneRenderer::update(const float delta_time, Scene* scene) {
    clearWindow();
    if (scene != nullptr) {
        updateScene(delta_time, scene);
    }
    if (_enable_imgui) {
        imguiUpdate();
    }
    presentToWindow();
}

void TXSceneRenderer::destroy() {
    destroyGraphicsAPI();
    imguiDestroy();
}

void TXSceneRenderer::enableImgui(const std::function<void()>& update_func) {
    _enable_imgui = true;
    _imgui_update = update_func;
}
void TXSceneRenderer::disableImgui() {
    _enable_imgui = false;
}

void TXSceneRenderer::loadFont(DPIScale const& dpi_scale) const {
    _io->Fonts->AddFontDefault();

    static constexpr float FONT_SIZE{24.0f};
    // add source hans font
    // Default + Selection of 2500 Ideographs used by Simplified Chinese
    const auto             font =
            _io->Fonts->AddFontFromMemoryCompressedTTF(source_han_sans_cn_font_compressed_data,// NOLINT
                                                       source_han_sans_cn_font_compressed_size, FONT_SIZE, nullptr,
                                                       // 这里包括了Latin范围
                                                       _io->Fonts->GetGlyphRangesChineseSimplifiedCommon());
    _io->FontDefault = font;

    // merge in icons from Font Awesome
    static constexpr std::array<ImWchar, 3> K_ICONS_RANGES{ICON_MIN_LC, ICON_MAX_LC, 0};
    static constexpr float                  ICONFONT_SIZE{24.0f};
    ImFontConfig                            icons_config;
    icons_config.MergeMode  = true;
    icons_config.PixelSnapH = true;
    _io->Fonts->AddFontFromMemoryCompressedBase85TTF(lucide_iconfont_compressed_data_base85,// NOLINT
                                                     ICONFONT_SIZE, &icons_config, K_ICONS_RANGES.data());

    _io->FontGlobalScale = dpi_scale.x_scale;
}

void TXSceneRenderer::loadStyle(DPIScale const& dpi_scale) {
    ImGui::StyleColorsDark();

    _style = &ImGui::GetStyle();

    // NOLINTBEGIN
    _style->WindowBorderSize         = 1.0f;
    _style->WindowRounding           = 8.0f;
    _style->PopupRounding            = 8.0f;
    _style->TabRounding              = 8.0;
    _style->FrameRounding            = 8.0;
    _style->GrabRounding             = 4.0;
    _style->WindowPadding            = {5.0f, 5.0f};
    _style->ItemSpacing              = {4.0f, 4.0f};
    _style->ItemInnerSpacing         = {3.0f, 3.0f};
    _style->WindowMenuButtonPosition = ImGuiDir::ImGuiDir_Left;
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
    // NOLINTEND

    constexpr ImVec4 BG                  = DEFAULT_STYLE_GROUP.background.toImVec4();
    constexpr ImVec4 FG                  = DEFAULT_STYLE_GROUP.foreground.toImVec4();
    constexpr ImVec4 TEXT                = DEFAULT_STYLE_GROUP.text.toImVec4();
    constexpr ImVec4 TEXT_BG             = DEFAULT_STYLE_GROUP.text_background.toImVec4();
    constexpr ImVec4 HIGHLIGHT_PRIMARY   = DEFAULT_STYLE_GROUP.highlight_primary.toImVec4();
    constexpr ImVec4 HOVER_PRIMARY       = DEFAULT_STYLE_GROUP.hover_primary.toImVec4();
    constexpr ImVec4 HIGHLIGHT_SECONDARY = DEFAULT_STYLE_GROUP.highlight_secondary.toImVec4();
    constexpr ImVec4 HOVER_SECONDARY     = DEFAULT_STYLE_GROUP.hover_secondary.toImVec4();
    constexpr ImVec4 MODAL_DIM           = DEFAULT_STYLE_GROUP.modal_dim.toImVec4();

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

    _style->ScaleAllSizes(dpi_scale.x_scale);
}

void TXSceneRenderer::initImguiForWindow(const Window* window) {
    if (window->getWindowAPI() == WindowAPI::GLFW) {
        ImGui_ImplGlfw_InitForVulkan(static_cast<const GLFWWindow*>(window)->getRawWindow(), true);
    }
}

void TXSceneRenderer::initImgui(const Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    _io = &ImGui::GetIO();

    _io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    _io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;    // Enable Docking
    _io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport
    // Platform Windows

    loadFont(window->dpi_scale());
    loadStyle(window->dpi_scale());

    initImguiForWindow(window);
    imguiForGraphicsAPIInit();
}

void TXSceneRenderer::imguiUpdate() {
    imguiGraphicsPreUpdate();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    _imgui_update();

    ImGui::Render();
    imguiGraphicsUpdate();
    if (_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void TXSceneRenderer::imguiDestroy() {
    imguiGraphicsDestroy();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void TXSceneRenderer::updateScene(float delta_time, Scene* scene) {
}

void TXSceneRenderer::imguiForGraphicsAPIInit() {
}

void TXSceneRenderer::initForGraphicsAPI(Window* window) {
    ResValT<std::unique_ptr<TXContext>> res = createTXContext(window);
    if (!res.has_value()) {
        FATAL_LOG("Failed to create TXContext");
        return;
    }
    this->_context = std::move(res.value());
}

void TXSceneRenderer::imguiGraphicsPreUpdate() {
}

void TXSceneRenderer::imguiGraphicsUpdate() {
}

void TXSceneRenderer::imguiGraphicsDestroy() {
}

void TXSceneRenderer::clearWindow() {
}

void TXSceneRenderer::presentToWindow() {
}

void TXSceneRenderer::destroyGraphicsAPI() {
}

}// namespace taixu
