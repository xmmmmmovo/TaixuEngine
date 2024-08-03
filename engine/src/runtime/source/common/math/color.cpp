//
// Created by xmmmmmovo on 2/16/2024.
//


#include "common/math/color.hpp"
#include "common/math/pack.hpp"

namespace taixu {

constexpr uint32_t Color::toUint32() const { return packUnorm4x8(_value); }

}// namespace taixu
