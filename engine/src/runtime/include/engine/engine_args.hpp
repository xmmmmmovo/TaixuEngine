//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP


#include "common/base/macro.hpp"
#include "common/hal/tx_string.hpp"

namespace taixu {

using namespace taixu::literals;

class EngineArgs {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN");
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, project_path, "");

    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_immediate_render_mode, false);

public:
    static constexpr tx_string_view LOCALE_ARG           = "--locale"_txsv;
    static constexpr tx_string_view PROJECT_PATH_ARG     = "--proj"_txsv;
    static constexpr tx_string_view IMMEDIATE_RENDER_ARG = "--immediate-render"_txsv;

private:
    static void registerWithArgs();

public:
    void initWithArgs(const std::vector<std::string>& args);
};

}// namespace taixu

#endif// TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
