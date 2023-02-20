//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include <spdlog/spdlog.h>


namespace taixu::editor {

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void  MainWindow::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        imgui_surface->Input_callback("FORWARD");
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        imgui_surface->Input_callback("BACKWARD");
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        imgui_surface->Input_callback("LEFT");
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        imgui_surface->Input_callback("RIGHT");
}

void MainWindow::mouse_callback(GLFWwindow* window, double xposIn,
                                double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    glm::vec2 mouse_pos(xposIn, yposIn);
    imgui_surface->Input_callback(mouse_pos);
    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void MainWindow::scroll_callback(GLFWwindow* window, double xoffset,
                                 double yoffset) {
    imgui_surface->Input_callback(static_cast<float>(yoffset));
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void MainWindow::init() {
    ///////////////////////////
    spdlog::info("Main window start init!");
    super::init();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    super::setIsVsync(true);
    imgui_surface->init(window);
    spdlog::info("Main window start finished!");
}

void MainWindow::update() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        imgui_surface->preUpdate();
        imgui_surface->update();
        super::update();
    }
}
void MainWindow::destroy() {
    imgui_surface->destroy();
    super::destroy();
}

}// namespace taixu::editor