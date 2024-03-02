//
// Created by xmmmmmovo on 1/19/2024.
//

#include "gameplay/gui/window.hpp"

#include "common/log/logger.hpp"

#include <common/base/macro.hpp>

#include <backends/imgui_impl_glfw.h>
#ifdef USE_VULKAN
    #include <backends/imgui_impl_vulkan.h>
#endif

#ifdef USE_DX11
    #include <backends/imgui_impl_dx11.h>
#endif

namespace taixu {

Window::Window(WindowInfo const& window_info) : _window_info(window_info) {}

void Window::init() {
    glfwSetErrorCallback(errorCallBack);

    if (GLFW_TRUE != glfwInit()) { FATAL_LOG("GLFW init failed!"); }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Window::showWindow() {
    _window = glfwCreateWindow(_window_info.width, _window_info.height,
                               _window_info.title.data(), nullptr, nullptr);

    if (!_window) {
        glfwTerminate();
        FATAL_LOG("Failed to create GLFW _window");
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

void Window::update() { handleEvents(); }

void Window::destroy() { glfwTerminate(); }

GLFWwindow* Window::getRawWindow() const { return _window; }

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