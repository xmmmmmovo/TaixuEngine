//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include <argparse/argparse.hpp>
#include <base/core.hpp>
#include <designs/public_singleton.hpp>
#include <log/logger.hpp>

namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;

    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN");

    PROTOTYPE_DFT_ONLY_GETTER(private, RenderAPI, render_api,
                              RenderAPI::VULKAN);

private:
    static constexpr const char* LOCALE = "--locale";

public:
    void loadParams(const std::vector<std::string>& args) {
        argparse::ArgumentParser program("TaixuEngineEditor");

        try {
            program.parse_args(args);
        } catch (const std::runtime_error& err) {
            std::cerr << err.what() << '\n';
            std::cerr << program;
            std::exit(1);
        }

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
