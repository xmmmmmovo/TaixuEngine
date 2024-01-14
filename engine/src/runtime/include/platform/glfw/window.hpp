//
// Created by xmmmmmovo on 11/14/2023.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8
#define ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8

#include "common/base/macro.hpp"
#include "gameplay/gui/window.hpp"

#define GLFW_INCLUDE_NONE
#ifdef VK_HEADER_VERSION
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#ifdef TX_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

#include <common/log/logger.hpp>

namespace taixu {

class GLFWWindow final : public Window {
private:
    GLFWwindow* _window{nullptr};

protected:
    static void errorCallBack(int error, const char* description) {
        FATAL_LOG("GLFW Error: {}, {}", error, description);
    }

    static void keyCallback(GLFWwindow* window, const int key,
                            const int scancode, const int action,
                            const int mods) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onKey(key, scancode, action, mods);
    }

    static void charCallback(GLFWwindow* window, const unsigned int codepoint) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onChar(codepoint);
    }

    static void charModsCallback(GLFWwindow*        window,
                                 const unsigned int codepoint, const int mods) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCharMods(codepoint, mods);
    }

    static void mouseButtonCallback(GLFWwindow* window, const int button,
                                    const int action, const int mods) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onMouseButton(button, action, mods);
    }

    static void cursorPosCallback(GLFWwindow* window, const double xpos,
                                  const double ypos) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCursorPos(xpos, ypos);
    }

    static void cursorEnterCallback(GLFWwindow* window, const int entered) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCursorEnter(entered);
    }

    static void scrollCallback(GLFWwindow* window, const double xoffset,
                               const double yoffset) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onScroll(xoffset, yoffset);
    }

    static void dropCallback(GLFWwindow* window, const int count,
                             const char** paths) {
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onDrop(count, paths);
    }

    static void windowSizeCallback(GLFWwindow* window, const int width,
                                   const int height) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->_width  = width;
        context->_height = height;
        context->onReset();
        context->onWindowSize(width, height);
    }

    static void windowDPIChangedCallback(GLFWwindow* window, const float xscale,
                                         const float yscale) {

        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->_dpi_scale.x_scale = xscale;
        context->_dpi_scale.y_scale = yscale;
        context->onWindowDPIChanged(xscale, yscale);
    }

    static void windowCloseCallback(GLFWwindow* window) {
        DEBUG_LOG("clicked close!");
        glfwSetWindowShouldClose(window, true);
        const auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onWindowClose();
    }

public:
    void init(const std::string_view& title, const int32_t width,
              const int32_t height) override {
        this->_title  = title;
        this->_width  = width;
        this->_height = height;

        glfwSetErrorCallback(errorCallBack);

        if (GLFW_TRUE != glfwInit()) { FATAL_LOG("GLFW init failed!"); }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    void showWindow() override {
        _window = glfwCreateWindow(_width, _height, _title.data(), nullptr,
                                   nullptr);

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

    void update() override { handleEvents(); }

    void handleEvents() override { glfwPollEvents(); }

    void destroy() override {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    ~GLFWWindow() override { destroy(); }

    [[nodiscard]] bool shouldClose() const override {
        return glfwWindowShouldClose(_window);
    }

    /**
     * below code only for windows that can get HWND
     */
#ifdef TX_WINDOWS
    [[nodiscard]] HWND getHWND() const override {
        return glfwGetWin32Window(_window);
    }

    [[nodiscard]] HINSTANCE getHINSTANCE() const override {
        return GetModuleHandle(nullptr);
    }
#endif
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8
