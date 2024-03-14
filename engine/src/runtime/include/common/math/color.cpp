//
// Created by xmmmmmovo on 2/16/2024.
//


#include "common/math/color.hpp"

#include "pack.hpp"

namespace taixu {

constexpr uint32_t Color::toUint32() const { return packUnorm4x8(value); }

}// namespace taixu