//
// Created by xmmmmmovo on 10/21/2023.
//

#ifndef ENGINE_SRC_COMMON_UTILS_BINARY_UTILS_B5AEEA67AB2146BD9C7F2945051AB18F
#define ENGINE_SRC_COMMON_UTILS_BINARY_UTILS_B5AEEA67AB2146BD9C7F2945051AB18F

#include "common/base/macro.hpp"


namespace taixu {

constexpr std::int32_t const ZERO_VALUE_FLAG = -1;

TX_INLINE std::int32_t bitScanForward32(std::uint32_t const value) {
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

TX_INLINE std::int32_t bitScanReverse32(std::uint32_t const value) {
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

#endif// ENGINE_SRC_COMMON_UTILS_BINARY_UTILS_B5AEEA67AB2146BD9C7F2945051AB18F
