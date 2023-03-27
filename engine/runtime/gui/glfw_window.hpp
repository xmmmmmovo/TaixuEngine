//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_GLFW_WINDOW_HPP
#define TAIXUENGINE_GLFW_WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

// "" headers
#include "core/base/macro.hpp"
#include "window.hpp"
#include "window_context.hpp"

namespace taixu {

inline GLFWwindow* initWindow(IWindowContext* context) {
    GLFWwindow* window = nullptr;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(context->width, context->height,
                              context->title.data(), nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to Create GLFW window!");
        glfwTerminate();
        exit(1);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        IWindowContext::errorCallBack(-1, "Failed to initialize GLAD");
        exit(1);
    }
    glfwSetWindowUserPointer(window, context);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return window;
}

inline void updateWindow(GLFWwindow* window) { glfwSwapBuffers(window); }
inline void destroyWindow(GLFWwindow* window) { glfwDestroyWindow(window); }

[[nodiscard]] inline bool shouldClose(GLFWwindow* window) {
    if (glfwWindowShouldClose(window)) { return true; }
    glfwPollEvents();
    return false;
}

inline void updateVsync(IWindowContext const& context) {
    if (context.is_vsync) {
        // turn off if you are using complex shader
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}


}// namespace taixu

#endif//TAIXUENGINE_GLFW_WINDOW_HPP
