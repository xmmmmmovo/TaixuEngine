//
// Created by xmmmmmovo on 2023/4/23.
//

#ifndef TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
#define TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP


#include "common/base/core.hpp"
#include "common/base/macro.hpp"

#include <string_view>

namespace taixu {

using namespace std::literals;

class EngineArgs {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN");

    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, EnumRenderAPI, render_api,
                                      EnumRenderAPI::DX11);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_editor, false);

public:
    static constexpr std::string_view LOCALE_ARG = "--locale"sv;
    static constexpr std::string_view EDITOR_ARG = "--editor"sv;

private:
    static void registerRendererFactory();

    static void registerWithArgs();

public:
    void initWithArgs(const std::vector<std::string>& args);
};

}// namespace taixu

#endif// TAIXUENGINE_RUNTIME_ENGINE_ARGS_HPP
