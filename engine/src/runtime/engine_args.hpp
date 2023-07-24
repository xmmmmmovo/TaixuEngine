//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include <argparse/argparse.hpp>
#include <common/base/public_singleton.hpp>
#include <runtime/management/graphics/render/render_api.hpp>
#include <spdlog/common.h>

namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;

    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, GraphicsAPI, api,
                                    GraphicsAPI::OPENGL);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, ShaderSourceType, source_type,
                                    ShaderSourceType::SOURCE);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN")

private:
    static constexpr const char* GRAPHICS_API       = "--graphics_api";
    static constexpr const char* SHADER_SOURCE_TYPE = "--shader_source_type";
    static constexpr const char* LOCALE             = "--locale";

public:
    void loadParams(const std::vector<std::string>& args) {
        argparse::ArgumentParser program("TaixuEngineEditor");

        program.add_argument(GRAPHICS_API)
                .default_value<std::string>("opengl")
                .help("Choose a graphics API");

        program.add_argument(SHADER_SOURCE_TYPE)
                .default_value<std::string>("source")
                .help("Choose a shader source type");

        try {
            program.parse_args(args);
        } catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
            std::cerr << program;
            std::exit(1);
        }

        auto const& api_param = program.get<std::string>(GRAPHICS_API);
        if (api_param == "opengl") {
            this->_api = GraphicsAPI::OPENGL;
        } else {
            std::cerr << "Invalid graphics API" << std::endl;
            std::exit(1);
        }

        auto const& source_type_param =
                program.get<std::string>(SHADER_SOURCE_TYPE);
        if (source_type_param == "source") {
            this->_source_type = ShaderSourceType::SOURCE;
        } else if (source_type_param == "spv") {
            this->_source_type = ShaderSourceType::SPV;
        } else {
            std::cerr << "Invalid shader source type" << std::endl;
            std::exit(1);
        }

#ifdef NDEBUG
        this->_is_debug = false;
        spdlog::set_level(spdlog::level::info);// Set global log level to debug
#else
        this->_is_debug = true;
        spdlog::set_level(spdlog::level::debug);// Set global log level to info
#endif
    }
};

}// namespace taixu

#endif// TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
