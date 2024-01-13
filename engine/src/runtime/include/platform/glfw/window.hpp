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
    void init(const std::string_view& title, int32_t width,
              int32_t height) override {
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
