//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include "spdlog/spdlog.h"
#include "clock_manager.h"

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        imgui_surface->Input_callback(glm::vec2(xPos, yPos));
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        imgui_surface->Input_callback(glm::vec2(xPos, yPos));
    }
    double xOffset, yOffset;
    glfwGetCursorPos(window, &xOffset, &yOffset);
    imgui_surface->Input_callback((float)yOffset);

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
    auto &clockManager = ClockManager::getInstance();
    auto &clock = clockManager.getClock("MainLoop");
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        imgui_surface->preUpdate();
        imgui_surface->update();
        super::update();
        double deltaTime = clock.getCurrentTime();
        // do something with deltaTime, e.g. print it
        std::cout << "Delta time: " << deltaTime << " s" << std::endl;
    }
}

void MainWindow::destroy() {
    imgui_surface->destroy();
    super::destroy();

}

void MainWindow::bindCallbacks() {

}

}// namespace taixu::editor