/**
 * @file engine_args.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-4-23
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/core.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

using namespace std::literals;

class EngineArgs {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_debug, true);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, locale, "zh_CN");
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, std::string, project_path, "");
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, WindowAPI, window_api, WindowAPI::GLFW);
    PROTOTYPE_DFT_ONLY_GETTER_CONST(private, RenderAPI, render_api, RenderAPI::VULKAN);

    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, bool, is_immediate_render_mode, false);

public:
    static constexpr auto LOCALE_ARG           = "--locale"sv;
    static constexpr auto PROJECT_PATH_ARG     = "--proj"sv;
    static constexpr auto IMMEDIATE_RENDER_ARG = "--immediate"sv;
    static constexpr auto WINDOW_API_ARG       = "--windowapi"sv;

private:
    static void registerWithArgs();

public:
    void initWithArgs(const std::vector<std::string>& args);
};

TX_NAMESPACE_END
