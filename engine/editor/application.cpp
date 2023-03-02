//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

// <> headers
#include "spdlog/spdlog.h"

// "" headers
#include "ui/main_window/main_window.hpp"

namespace taixu::editor {

/**
 * @brief init spdlog config
 */
void initSpdlog() {
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
}

void Application::initApplicationArgs(int argc, char *argv[]) {}

void Application::initialize(int argc, char *argv[]) {
    initSpdlog();
    initApplicationArgs(argc, argv);
    std::shared_ptr<MainWindow> window_ptr =
            std::make_shared<MainWindow>(MainWindowContext{
                    MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE});
    window_ptr->init();
    Engine *instance = &Engine::getInstance();
    instance->init();
    this->window = window_ptr;
}

void Application::run() { this->window->update(); }

void Application::destroy() { this->window->destroy(); }
}// namespace taixu::editor