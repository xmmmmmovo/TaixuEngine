//
// Created by xmmmmmovo on 2/16/2024.
//

#include "color.hpp"

#include "pack.hpp"

namespace taixu {

constexpr ImVec4 Color::toImVec4() {
    return {value.x, value.y, value.z, value.z};
}

constexpr uint32_t Color::toUint32() const { return packUnorm4x8(value); }

}// namespace taixu