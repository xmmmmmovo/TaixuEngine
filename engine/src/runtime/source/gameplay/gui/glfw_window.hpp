/**
 * @file glfw_window.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-09
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/gameplay/gui/window.hpp"

#define GLFW_INCLUDE_NONE
#ifdef USE_VULKAN
    #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#ifdef TX_WINDOWS
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif

namespace taixu {

struct VkGlfwExtensions {
    uint32_t                 count{0};
    std::vector<const char*> names{};
};

class GLFWWindow final : public Window {
public:
    void init() override;
    void showWindow() override;

    void                    destroy() override;
    void                    handleEvents() override;
    [[nodiscard]] bool      shouldClose() const override;
    [[nodiscard]] WindowAPI getWindowAPI() const override;

    [[nodiscard]] GLFWwindow*             getRawWindow() const;
    [[nodiscard]] static bool             isSupportVulkanImpl();
    [[nodiscard]] static VkGlfwExtensions getVulkanInstanceExtensions();

#ifdef TX_WINDOWS
    [[nodiscard]] HWND getHWND() const {
        return glfwGetWin32Window(_window);
    }

    [[nodiscard]] static HINSTANCE getHINSTANCE() {
        return GetModuleHandle(nullptr);
    }
#endif

private:
    static void errorCallBack(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void charCallback(GLFWwindow* window, unsigned int codepoint);
    static void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void cursorEnterCallback(GLFWwindow* window, int entered);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void dropCallback(GLFWwindow* window, int count, const char** paths);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void windowDPIChangedCallback(GLFWwindow* window, float xscale, float yscale);
    static void windowCloseCallback(GLFWwindow* window);

private:
    GLFWwindow* _window{nullptr};
    void        updateTitle(const char* title) override;

public:
    GLFWWindow(WindowInfo const& window_info) : Window(window_info) {
    }
};

}// namespace taixu
