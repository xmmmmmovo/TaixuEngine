//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.h"

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
    this->window = std::make_shared<MainWindow>();
    this->window->init();
    spdlog::debug("app init!");
}

void Application::run() { this->window->render(); }

}// namespace taixu::editor