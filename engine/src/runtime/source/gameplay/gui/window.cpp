//
// Created by xmmmmmovo on 1/19/2024.
//

#include "gameplay/gui/window.hpp"

#include "IconsFontAwesome6.h"
#include "ImGuizmo.h"
#include "common/log/logger.hpp"
#include "imgui.h"
#include "imgui_internal.h"

#include <common/base/macro.hpp>

#include <backends/imgui_impl_glfw.h>
#ifdef USE_VULKAN
    #include <backends/imgui_impl_vulkan.h>
#endif

#ifdef USE_DX11
    #include <backends/imgui_impl_dx11.h>
#endif

namespace taixu {

void Window::loadCNFont() const {
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

void Window::loadStyle() {
    _io->ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
    // Gamepad Controls
    _io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking
    _io->ConfigFlags |=
            ImGuiConfigFlags_ViewportsEnable;// Enable Multi-Viewport
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

void Window::initForWindow() const {
    ImGui_ImplGlfw_InitForOther(_window, true);
}

void Window::initForGraphicsAPI() {}

void Window::init(WindowInfo const& info) {
    this->_window_info = info;

    glfwSetErrorCallback(errorCallBack);

    if (GLFW_TRUE != glfwInit()) { FATAL_LOG("GLFW init failed!"); }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Window::initForImgui() {
    if (_window == nullptr) {
        FATAL_LOG("Cannot init imgui before window created!");
    }
    this->_imgui_enabled = true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    _io = &ImGui::GetIO();

    loadCNFont();
    loadStyle();
}

void Window::addComponents(const ImguiComponent& imgui_component) {
    _components.emplace_back(imgui_component);
}

void Window::showWindow() {
    _window = glfwCreateWindow(
            this->_window_info.width, this->_window_info.height,
            this->_window_info.title.data(), nullptr, nullptr);

    if (!_window) {
        glfwTerminate();
        FATAL_LOG("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(_window, this);

    glfwSetKeyCallback(_window, keyCallback);
    glfwSetErrorCallback(errorCallBack);
    glfwSetCharCallback(_window, charCallback);
    glfwSetCharModsCallback(_window, charModsCallback);
    glfwSetMouseButtonCallback(_window, mouseButtonCallback);
    glfwSetCursorPosCallback(_window, cursorPosCallback);
    glfwSetCursorEnterCallback(_window, cursorEnterCallback);
    glfwSetScrollCallback(_window, scrollCallback);
    glfwSetDropCallback(_window, dropCallback);
    glfwSetWindowSizeCallback(_window, windowSizeCallback);
    glfwSetWindowCloseCallback(_window, windowCloseCallback);
    glfwSetWindowContentScaleCallback(_window, windowDPIChangedCallback);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::update() {
    handleEvents();
    // Rendering
    if (_imgui_enabled) {
        ImGui::NewFrame();

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        for (const auto& [name, update_func, flags, open] : _components) {
            // render the components
            if (!ImGui::Begin(name.data(), open, flags)) {
                ImGui::End();
                return;
            }
            update_func();
            ImGui::End();
        }

        ImGui::Render();


        if (_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }
}

void Window::destroy() {
    glfwTerminate();
    if (_imgui_enabled) { ImGui::DestroyContext(); }
}

void Window::handleEvents() { glfwPollEvents(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(_window); }


void Window::errorCallBack(int error, const char* description) {
    FATAL_LOG("GLFW Error: {}, {}", error, description);
}

void Window::keyCallback(GLFWwindow* window, const int key, const int scancode,
                         const int action, const int mods) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onKey(key, scancode, action, mods);
}


void Window::charCallback(GLFWwindow* window, const unsigned codepoint) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onChar(codepoint);
}

void Window::charModsCallback(GLFWwindow* window, const unsigned codepoint,
                              const int mods) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCharMods(codepoint, mods);
}

void Window::mouseButtonCallback(GLFWwindow* window, const int button,
                                 const int action, const int mods) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onMouseButton(button, action, mods);
}

void Window::cursorPosCallback(GLFWwindow* window, const double xpos,
                               const double ypos) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCursorPos(xpos, ypos);
}

void Window::cursorEnterCallback(GLFWwindow* window, const int entered) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onCursorEnter(entered);
}
void Window::scrollCallback(GLFWwindow* window, const double xoffset,
                            const double yoffset) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onScroll(xoffset, yoffset);
}

void Window::dropCallback(GLFWwindow* window, const int count,
                          const char** paths) {
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onDrop(count, paths);
}

void Window::windowSizeCallback(GLFWwindow* window, const int width,
                                const int height) {
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->_window_info.width  = width;
    context->_window_info.height = height;
    context->onReset();
    context->onWindowSize(width, height);
}

void Window::windowDPIChangedCallback(GLFWwindow* window, const float xscale,
                                      const float yscale) {
    DEBUG_LOG("dpi changed: {}, {}", xscale, yscale);
    auto* context = static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->_dpi_scale.x_scale = xscale;
    context->_dpi_scale.y_scale = yscale;
    context->onWindowDPIChanged(xscale, yscale);
}

void Window::windowCloseCallback(GLFWwindow* window) {
    DEBUG_LOG("clicked close!");
    glfwSetWindowShouldClose(window, true);
    const auto* context =
            static_cast<Window*>(glfwGetWindowUserPointer(window));
    context->onWindowClose();
}

}// namespace taixu