//
// Created by xmmmmmovo on 1/19/2024.
//

#include "common/utils/binary_utils.hpp"

constexpr std::int32_t const ZERO_VALUE_FLAG = -1;

namespace taixu {

std::int32_t bitScanForward32(std::uint32_t const value) {
    if (value == 0) { return ZERO_VALUE_FLAG; }

#ifdef _MSC_VER
    unsigned long index{0};
    _BitScanForward(&index, value);
    return static_cast<std::int32_t>(index);
#elif __GNUC__
    int zero_cnt = __builtin_clz(value);
    return zero_cnt;
#else
    static_assert(false, "Unsupported compiler");
#endif
}

std::int32_t bitScanReverse32(std::uint32_t const value) {
    if (value == 0) { return ZERO_VALUE_FLAG; }

#ifdef _MSC_VER
    unsigned long index{0};
    _BitScanReverse(&index, value);
    return static_cast<std::int32_t>(index);
#elif __GNUC__
    int zero_cnt = __builtin_ctz(value);
    return zero_cnt;
#else
    static_assert(false, "Unsupported compiler");
#endif
}

}// namespace taixu