//
// Created by xmmmmmovo on 1/24/2024.
//

#include "engine/engine_args.hpp"

#include <argparse/argparse.hpp>

#include "management/graphics/rhi/tx_renderer_factory.hpp"
#include "platform/dx11/dx11_scene_renderer.hpp"

namespace taixu {


void EngineArgs::registerRendererFactory() {
    SceneRendererFactory::registerCreationFunc(RenderAPI::DX11, [] {
        return std::make_unique<DX11SceneRenderer>();
    });
}

void EngineArgs::registerWithArgs() { registerRendererFactory(); }


void EngineArgs::initWithArgs(const std::vector<std::string>& args) {
    argparse::ArgumentParser program("TaixuEngineEditor");

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
}

}// namespace taixu