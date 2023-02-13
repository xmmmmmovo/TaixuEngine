//
// Created by xmmmmmovo on 2023/2/13.
//

#include "glfw_window.hpp"
#include "core/base/macro.hpp"

namespace taixu::gui {

void TX_GLFWwindow::init() {
    if (window != nullptr) { return; }
    if (!initialized) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, core::OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, core::OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        initialized = true;
    }

    window = glfwCreateWindow(context.width, context.height,
                              context.title.data(), nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to Create GLFW window!");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    // turn off if you are using complex shader
    glfwSwapInterval(1);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        errorCallBack(-1, "Failed to initialize GLAD");
        exit(1);
    }
    glfwSetWindowUserPointer(window, &context);
}
void TX_GLFWwindow::render() {}
void TX_GLFWwindow::destroy() {}

void TX_GLFWwindow::errorCallBack(int error, const char *description) {
    spdlog::error("GLFW Error: {}", description);
}

}// namespace taixu::gui
