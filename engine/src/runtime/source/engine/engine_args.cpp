//
// Created by xmmmmmovo on 1/24/2024.
//

#include "engine/engine_args.hpp"

#include <argparse/argparse.hpp>

#include "management/scene/tx_renderer_factory.hpp"
#include "platform/dx11/dx11_scene_renderer.hpp"

namespace taixu {


void EngineArgs::registerRendererFactory() {
    SceneRendererFactory::registerCreationFunc(EnumRenderAPI::DX11, [] {
        return std::make_unique<DX11SceneRenderer>();
    });
}

void EngineArgs::registerWithArgs() { registerRendererFactory(); }


void EngineArgs::initWithArgs(const std::vector<std::string>& args) {
    INFO_LOG("Loading engine arguments...");
    argparse::ArgumentParser program("TaixuEngineEditor");

    program.add_argument(EDITOR_ARG)
            .help("Is the editor mode")
            .default_value(false)
            .implicit_value(true);

    program.add_argument(IMMEDIATE_RENDER_ARG)
            .help("Is use immediate rendering mode")
            .default_value(false)
            .implicit_value(true);


    try {
        program.parse_args(args);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << '\n';
        std::cerr << program;
        std::exit(1);
    }

    registerWithArgs();

#ifdef NDEBUG
    this->_is_debug = false;
    Logger::setLevel(Logger::LogLevel::INFO);// Set global log level to debug
#else
    this->_is_debug = true;
    Logger::setLevel(Logger::LogLevel::DEBUG);// Set global log level to info
#endif

    _is_editor                = program.get<bool>(EDITOR_ARG);
    _is_immediate_render_mode = program.get<bool>(IMMEDIATE_RENDER_ARG);

    INFO_LOG("Is debug mode: {}", _is_debug);
    INFO_LOG("Is editor mode: {}", _is_editor);
    INFO_LOG("Is immediate render mode: {}", _is_immediate_render_mode);
}

}// namespace taixu