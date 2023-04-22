//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

#include <argparse/argparse.hpp>
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

void Application::initApplicationArgs(std::vector<std::string> const &args) {
    argparse::ArgumentParser program("TaixuEngineEditor");
    try {
        program.parse_args(args);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
}

void Application::initialize(std::vector<std::string> const &args) {
    spdlog::info("start initialize the application!");
    initSpdlog();
    initApplicationArgs(args);

    _context_ptr = std::make_unique<WindowContext>(
            MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, MAIN_WINDOW_TITLE);

    InputSystem::getInstance().setContext(_context_ptr.get());

    // init window pointer
    std::unique_ptr<MainWindow> window_ptr_local =
            std::make_unique<MainWindow>(_context_ptr.get());
    // init window
    window_ptr_local->init();

    _engine_ptr->init(_context_ptr.get());

    window_ptr_local->initWithEngineRuntime(_engine_ptr);
    this->_window_ptr = std::move(window_ptr_local);
    spdlog::info("initialize the application finished!");
}

void Application::run() {
    while (!this->_context_ptr->shouldClose()) {
        this->_engine_ptr->getRenderer()->clearSurface();
        this->_engine_ptr->update();
        this->_window_ptr->update();
    }
}

void Application::destroy() { this->_window_ptr->destroy(); }
}// namespace taixu::editor