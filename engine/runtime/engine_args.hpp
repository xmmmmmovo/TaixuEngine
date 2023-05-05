//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP

#include "argparse/argparse.hpp"
#include "core/base/public_singleton.hpp"
#include "management/graphics/render/render_api.hpp"

namespace taixu {

class EngineArgs : public PublicSingleton<EngineArgs> {
    friend class PublicSingleton<EngineArgs>;
    
public:
    GraphicsAPI api{GraphicsAPI::OPENGL};

    void loadParams(const std::vector<std::string> &args) {
        argparse::ArgumentParser program("TaixuEngineEditor");

        program.add_argument("-api", "--graphics_api")
                .default_value("opengl")
                .help("Choose a graphics API")
                .action([](std::string const &val) {
                    taixu::EngineArgs &args_ins =
                            taixu::EngineArgs::getInstance();

                    if ("opengl" == val) {
                        args_ins.api = taixu::GraphicsAPI::OPENGL;
                    } else {
                        throw std::runtime_error(
                                "Invalid graphics API choice: " + val);
                    }
                });

        try {
            program.parse_args(args);
        } catch (const std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
            std::cerr << program;
            std::exit(1);
        }
    }
};

}// namespace taixu

#endif//TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
