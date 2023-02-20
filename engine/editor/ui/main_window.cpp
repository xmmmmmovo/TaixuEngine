//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include <spdlog/spdlog.h>


namespace taixu::editor {

void MainWindow::init() {
    ///////////////////////////
    spdlog::info("Main window start init!");
    super::init();
    super::setIsVsync(true);
    imgui_surface->init(window);
    spdlog::info("Main window start finished!");
}

void MainWindow::update() {
    while (!glfwWindowShouldClose(window)) {
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