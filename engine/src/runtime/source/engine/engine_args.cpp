//
// Created by xmmmmmovo on 1/24/2024.
//

#include "engine/engine_args.hpp"

#include "common/log/logger.hpp"

#include <argparse/argparse.hpp>


namespace taixu {
void EngineArgs::registerWithArgs() {}

void EngineArgs::initWithArgs(const std::vector<std::string>& args) {
    INFO_LOG("Loading engine arguments...");
    argparse::ArgumentParser program("TaixuEngineRuntime");

    program.add_argument(IMMEDIATE_RENDER_ARG)
            .help("Is use immediate rendering mode")
            .default_value(false)
            .implicit_value(true);

    program.add_argument(PROJECT_PATH_ARG).help("Load project path").default_value(tx_string(""));

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

    INFO_LOG("Is debug mode: {}", _is_debug);
    INFO_LOG("Is immediate render mode: {}", _is_immediate_render_mode);
    INFO_LOG("Load project path: {}", _project_path);
}

}// namespace taixu
