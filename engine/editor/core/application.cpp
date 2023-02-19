//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

// <> headers
#include <spdlog/spdlog.h>

// "" headers
#include "ui/main_window.hpp"

namespace taixu::editor {

void initSpdlog() {
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
}

void initApplicationArgs() {}

void Application::initialize() {
    initSpdlog();
    initApplicationArgs();
    this->window = std::make_shared<MainWindow>(gui::IWindowContext{
            MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE});
    this->window->init();
}

void Application::run() { this->window->update(); }

void Application::destroy() { this->window->destroy(); }

std::shared_ptr<ApplicationContext> Application::getContext() {
    return context;
}

}// namespace taixu::editor