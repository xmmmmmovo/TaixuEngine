//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include <argparse/argparse.hpp>
#include <common/base/public_singleton.hpp>
#include <runtime/management/graphics/render/render_api.hpp>

namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;

    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, GraphicsAPI, api,
                                    GraphicsAPI::OPENGL);

private:
    static constexpr const char *GRAPHICS_API = "--graphics_api";

public:
    void loadParams(const std::vector<std::string> &args) {
        argparse::ArgumentParser program("TaixuEngineEditor");

        program.add_argument(GRAPHICS_API)
                .default_value<std::string>("opengl")
                .help("Choose a graphics API");

        try {
            program.parse_args(args);
        } catch (const std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
            std::cerr << program;
            std::exit(1);
        }

        auto const &api_param = program.get<std::string>(GRAPHICS_API);
        if (api_param == "opengl") {
            this->_api = GraphicsAPI::OPENGL;
        } else {
            std::cerr << "Invalid graphics API" << std::endl;
            std::exit(1);
        }
    }
};

}// namespace taixu

#endif//TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
