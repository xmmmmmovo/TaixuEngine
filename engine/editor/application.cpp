//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

// <> headers
#include "spdlog/spdlog.h"

// "" headers
#include "gui/input_system.hpp"
#include "ui/main_window/main_window.hpp"

namespace taixu::editor {

/**
 * @brief initWindow spdlog config
 */
void initSpdlog() {
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
}

void Application::initApplicationArgs(int argc, char *argv[]) {}

void Application::initialize(int argc, char *argv[]) {
    initSpdlog();
    initApplicationArgs(argc, argv);

    context_ptr = std::make_shared<WindowContext>(
            MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE);

    InputSystem::getInstance().setContext(context_ptr);

    // init window pointer
    std::shared_ptr<MainWindow> window_ptr_local =
            std::make_shared<MainWindow>(context_ptr);
    // init window
    window_ptr_local->init();

    _engine_ptr->init();
    window_ptr_local->setEngineRuntime(_engine_ptr);
    this->window_ptr = window_ptr_local;
}

void Application::run() {
    while (!this->context_ptr->shouldClose()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        this->_engine_ptr->update();
        this->window_ptr->update();
    }
}

void Application::destroy() { this->window_ptr->destroy(); }
}// namespace taixu::editor