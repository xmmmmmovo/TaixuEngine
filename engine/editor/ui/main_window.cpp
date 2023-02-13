//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
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

    this->imguiSurface     = std::make_unique<gui::ImguiSurface>();
    this->renderComponent  = std::make_unique<RenderComponent>();
    this->controlComponent = std::make_unique<ControlComponent>();

    imguiSurface->init(window);
    controlComponent->init();
    renderComponent->init();
    spdlog::info("Main window start finished!");
}

void MainWindow::update() {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        imguiSurface->pre_update();
        renderComponent->update();
        controlComponent->update();
        imguiSurface->update();
        super::update();
        processInput(window);
    }
}
void MainWindow::destroy() {
    imguiSurface->destroy();
    super::destroy();
}

}// namespace taixu::editor