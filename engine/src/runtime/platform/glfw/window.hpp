//
// Created by xmmmmmovo on 11/14/2023.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8
#define ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8

#include "gameplay/gui/window.hpp"

#ifdef _WIN32
    #include "platform/os/windows/windows_headers.hpp"
#endif

#define GLFW_INCLUDE_NONE
#ifdef VK_HEADER_VERSION
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

#include <common/log/logger.hpp>

namespace taixu {

class GLFWWindow final : public Window {
private:
    GLFWwindow* _window;

protected:
    static void errorCallBack(int error, const char* description) {
        FATAL_LOG("GLFW Error: {}, {}", error, description);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode,
                            int action, int mods) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onKey(key, scancode, action, mods);
    }

    static void charCallback(GLFWwindow* window, unsigned int codepoint) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onChar(codepoint);
    }

    static void charModsCallback(GLFWwindow* window, unsigned int codepoint,
                                 int mods) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCharMods(codepoint, mods);
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                    int mods) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onMouseButton(button, action, mods);
    }

    static void cursorPosCallback(GLFWwindow* window, double xpos,
                                  double ypos) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCursorPos(xpos, ypos);
    }

    static void cursorEnterCallback(GLFWwindow* window, int entered) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onCursorEnter(entered);
    }

    static void scrollCallback(GLFWwindow* window, double xoffset,
                               double yoffset) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onScroll(xoffset, yoffset);
    }

    static void dropCallback(GLFWwindow* window, int count,
                             const char** paths) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onDrop(count, paths);
    }

    static void windowSizeCallback(GLFWwindow* window, int width, int height) {
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->_width  = width;
        context->_height = height;
        context->onReset();
        context->onWindowSize(width, height);
    }

    static void windowCloseCallback(GLFWwindow* window) {
        DEBUG_LOG("clicked close!");
        glfwSetWindowShouldClose(window, true);
        auto* context =
                static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        context->onWindowClose();
    }

public:
    void init() override {
        glfwSetErrorCallback(errorCallBack);

        if (GLFW_TRUE != glfwInit()) { FATAL_LOG("GLFW init failed!"); }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }

    void showWindow(std::string_view const& title, int32_t width,
                    int32_t height) override {
        _window =
                glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

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
#ifdef _WIN32
    [[nodiscard]] std::optional<HWND> getHWND() const {
        if (!_window) {
            ERROR_LOG("window have not created!");
            return std::nullopt;
        }
        return glfwGetWin32Window(_window);
    }

    [[nodiscard]] std::optional<HINSTANCE> getHINSTANCE() const {
        if (!_window) {
            ERROR_LOG("window have not created!");
            return std::nullopt;
        }
        return GetModuleHandle(nullptr);
    }
#endif
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_GLFW_WINDOW_039D648EBA9E48E3A7B82825AD1D92E8
