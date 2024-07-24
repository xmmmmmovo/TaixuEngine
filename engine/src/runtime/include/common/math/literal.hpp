//
// Created by xmmmmmovo on 2/16/2024.
//

#pragma once

#include <cstdint>

namespace taixu::literal {

static constexpr uint8_t UC_MAX{255};

constexpr uint8_t operator"" _uc(const uint64_t value) {
    if (value > UC_MAX) { return UC_MAX; }
    return static_cast<uint8_t>(value);
}

}// namespace taixu::literal