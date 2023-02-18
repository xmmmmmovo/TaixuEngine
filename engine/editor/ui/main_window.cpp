//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include <spdlog/spdlog.h>


namespace taixu::editor {

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
    imguiSurface->init(window);
    spdlog::info("Main window start finished!");
}

void MainWindow::update() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        imguiSurface->preUpdate();
        imguiSurface->update();
        super::update();
    }
}
void MainWindow::destroy() {
    imguiSurface->destroy();
    super::destroy();
}

}// namespace taixu::editor