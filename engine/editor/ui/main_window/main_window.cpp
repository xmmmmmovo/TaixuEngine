//
// Created by xmmmmmovo on 2023/2/12.
//

#include "main_window.hpp"

#include "resource/project_manager.hpp"
#include "spdlog/spdlog.h"

namespace taixu::editor {

void MainWindow::init() {
    ///////////////////////////
    spdlog::info("Main window start init!");
    super::init(this->context);
    super::setIsVsync(true);
    ProjectManager manager;

    main_imgui_surface->init(window);
    spdlog::info("Main window start finished!");
}

void MainWindow::update() {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        main_imgui_surface->preUpdate();
        main_imgui_surface->update();
        super::update();
    }
}

void MainWindow::destroy() {
    main_imgui_surface->destroy();
    delete this->context;
    super::destroy();
}

void MainWindow::setEngineRuntime(Engine *engine_runtime_ptr) {
    this->engine_runtime = engine_runtime_ptr;
    this->renderer       = engine_runtime_ptr->getRenderer();
}

}// namespace taixu::editor