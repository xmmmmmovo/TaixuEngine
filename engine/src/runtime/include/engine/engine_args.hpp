//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include <argparse/argparse.hpp>

#include <common/base/core.hpp>
#include <common/designs/public_singleton.hpp>
#include <common/log/logger.hpp>
#include <gameplay/gui/window_factory.hpp>
#include <management/graphics/rhi/tx_renderer_factory.hpp>
#include <platform/dx11/dx11_scene_renderer.hpp>
#include <platform/glfw/window.hpp>

namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;

    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN");

    PROTOTYPE_DFT_ONLY_GETTER(private, RenderAPI, render_api, RenderAPI::DX11);

private:
    static constexpr const char* LOCALE = "--locale";

private:
    static void registerWindowFactory() {
        WindowFactory::registerRenderAPI(RenderAPI::VULKAN, WindowAPI::GLFW);
        WindowFactory::registerRenderAPI(RenderAPI::DX11, WindowAPI::GLFW);
        WindowFactory::registerRenderAPI(RenderAPI::DX12, WindowAPI::GLFW);

        WindowFactory::registerCreationFunc(WindowAPI::GLFW, []() {
            return std::make_unique<GLFWWindow>();
        });
    }

    static void registerRendererFactory() {
        SceneRendererFactory::registerCreationFunc(RenderAPI::DX11, []() {
            return std::make_unique<DX11SceneRenderer>();
        });
    }

    void registerWithArgs() {
        registerWindowFactory();
        registerRendererFactory();
    }

public:
    void initWithArgs(const std::vector<std::string>& args) {
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
        Logger::setLevel(
                Logger::LogLevel::INFO);// Set global log level to debug
#else
        this->_is_debug = true;
        Logger::setLevel(
                Logger::LogLevel::DEBUG);// Set global log level to info
#endif
    }
};

}// namespace taixu

#endif// TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP