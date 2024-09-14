//
// Created by xmmmmmovo on 1/26/2024.
//

#pragma once

#include <corecrt_math_defines.h>

#include "trigonometric.hpp"

namespace taixu::literals {

constexpr auto operator"" _radf(const long double value) noexcept -> decltype(toRadians(static_cast<float>(value))) {
    return toRadians(static_cast<float>(value));
}

constexpr auto operator"" _degf(const long double value) noexcept -> decltype(toDegrees(static_cast<float>(value))) {
    return toDegrees(static_cast<float>(value));
}


}// namespace taixu::literals
