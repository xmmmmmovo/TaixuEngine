//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include <spdlog/spdlog.h>

namespace taixu::editor {
void MainWindow::init() {
    spdlog::info("Main window start init!");


    spdlog::info("Main window start finished!");
}
void MainWindow::render() {}
MainWindow::~MainWindow() { glfwDestroyWindow(window); }
}// namespace taixu::editor