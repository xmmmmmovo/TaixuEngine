//
// Created by xmmmmmovo on 1/24/2024.
//

#include <argparse/argparse.hpp>

#include "common/log/custom_fmt.hpp"
#include "gameplay/gui/glfw_window.hpp"
#include "taixu/common/log/logger.hpp"
#include "taixu/engine/engine_args.hpp"
#include "taixu/gameplay/gui/window_factory.hpp"

namespace taixu {

void EngineArgs::registerWithArgs() {
    WindowFactory::registerCreationFunc(
            WindowAPI::GLFW, [](WindowInfo window_info) { return std::make_unique<GLFWWindow>(window_info); });
}

void EngineArgs::initWithArgs(const std::vector<std::string>& args) {
    INFO_LOG("Loading engine arguments...");
    argparse::ArgumentParser program("TaixuEngineRuntime");

    program.add_argument(IMMEDIATE_RENDER_ARG)
            .help("Is use immediate rendering mode")
            .default_value(false)
            .implicit_value(true);
    program.add_argument(PROJECT_PATH_ARG).help("Load project path").default_value(std::string(""));
    program.add_argument(WINDOW_API_ARG).help("Window api").default_value(WindowAPI::GLFW);

    try {
        program.parse_args(args);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << '\n';
        std::cerr << program;
        std::exit(1);
    }

    registerWithArgs();

#ifdef TX_DEBUG
    this->_is_debug = true;
    Logger::setLevel(Logger::LogLevel::DEBUG);// Set global log level to debug
#else
    this->_is_debug = false;
    Logger::setLevel(Logger::LogLevel::INFO);// Set global log level to info
#endif

    _is_immediate_render_mode = program.get<bool>(IMMEDIATE_RENDER_ARG);
    _project_path             = program.get<std::string>(PROJECT_PATH_ARG);
    _window_api               = program.get<WindowAPI>(WINDOW_API_ARG);

    INFO_LOG("Is debug mode: {}", _is_debug);
    INFO_LOG("Is immediate render mode: {}", _is_immediate_render_mode);
    INFO_LOG("Load project path: {}", _project_path);
    INFO_LOG("Window API: {}", _window_api);
}

}// namespace taixu
