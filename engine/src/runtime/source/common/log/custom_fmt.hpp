/**
 * @file custom_fmt.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <fmt/core.h>
#include <magic_enum.hpp>


#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

// Generic fmt::formatter for any enum
template<typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_enum_v<T>, char>> {
    constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const T& value, FormatContext& ctx) -> decltype(ctx.out()) {
        // Use magic_enum to convert enum to string
        auto name = magic_enum::enum_name(value);
        return fmt::format_to(ctx.out(), "{}", name.empty() ? "Unknown Enum" : name);
    }
};

TX_NAMESPACE_END
