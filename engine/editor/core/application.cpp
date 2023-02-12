//
// Created by xmmmmmovo on 2023/2/12.
//

#include "application.hpp"

// <> headers
#include <spdlog/spdlog.h>

namespace taixu::editor {

void initSpdlog() {
    spdlog::set_level(spdlog::level::debug);// Set global log level to debug
}

void initApplicationArgs() {}

void Application::initialize() {
    initSpdlog();
    initApplicationArgs();
}

void Application::run() {}

}// namespace taixu::editor