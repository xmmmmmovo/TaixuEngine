//
// Created by xmmmmmovo on 2/16/2024.
//

#pragma once

#include "literal.hpp"
#include "vec.hpp"

#include "common/base/macro.hpp"

#include "imgui.h"

namespace taixu {

class Color {
private:
    static constexpr uint8_t MAX_COLOR = 255;

public:
    Vec4 value{};

    explicit constexpr Color(const Vec4 color_val) : value(color_val) {}

    explicit constexpr Color(const float r, const float g, const float b,
                             const float a)
        : value{r, g, b, a} {}

    explicit constexpr Color(const uint8_t r, const uint8_t g, const uint8_t b,
                             const uint8_t a)
        : value{
                  static_cast<float>(r) / MAX_COLOR,
                  static_cast<float>(g) / MAX_COLOR,
                  static_cast<float>(b) / MAX_COLOR,
                  static_cast<float>(a) / MAX_COLOR,
          } {}

    constexpr ImVec4 toImVec4();

    [[nodiscard]] constexpr uint32_t toUint32() const;
};

namespace color {
    using namespace literal;

    TX_INLINE constexpr Color WHITE_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
    TX_INLINE constexpr Color BLACK_COLOR{0.0f, 0.0f, 0.0f, 1.0f};
    TX_INLINE constexpr Color RED_COLOR{1.0f, 0.0f, 0.0f, 1.0f};
    TX_INLINE constexpr Color GREEN_COLOR{0.0f, 1.0f, 0.0f, 1};
    TX_INLINE constexpr Color BLUE_COLOR{0.0f, 0.0f, 1.0f, 1.0f};
    TX_INLINE constexpr Color GRASS_COLOR{110_uc, 138_uc, 92_uc, 255_uc};
    TX_INLINE constexpr Color BACKGROUND_COLOR{42_uc, 44_uc, 53_uc, 255_uc};
    TX_INLINE constexpr Color BACKGROUND_DARK_COLOR{30_uc, 31_uc, 38_uc,
                                                    255_uc};
}// namespace color

}// namespace taixu