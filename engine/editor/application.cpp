//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

#include <string_view>
#include <vector>

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
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
#else
    spdlog::set_level(spdlog::level::info);// Set global log level to info
#endif
}

void Application::initApplicationArgs(
        std::vector<std::string_view> const &args) {}

void Application::initialize(std::vector<std::string_view> const &args) {
    initSpdlog();
    initApplicationArgs(args);

    context_ptr = std::make_unique<WindowContext>(
            MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE);

    InputSystem::getInstance().setContext(context_ptr.get());

    // init window pointer
    std::unique_ptr<MainWindow> window_ptr_local =
            std::make_unique<MainWindow>(context_ptr.get());
    // init window
    window_ptr_local->init();

    _engine_ptr->init();
    window_ptr_local->setEngineRuntime(_engine_ptr);
    this->window_ptr = std::move(window_ptr_local);
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