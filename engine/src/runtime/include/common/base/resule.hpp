/**
 * @file resule.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "common/base/core.hpp"

namespace taixu {
/**
 * @brief Concept type limit for EnumTXResult
 *
 * @tparam T
 */
template<typename T>
concept RetCodeConcept = std::is_enum_v<T> && std::is_same_v<T, RetCode>;

template<typename T>
using ResValT = std::expected<T, RetCode>;

#define EXPECTED ::std::expected
#define UNEXPECTED ::std::unexpected

template<typename T>
ResValT<T> createResVal(RetCode result_code, T& value) {
    return ResValT<T>(result_code, value);
}

template<typename T>
ResValT<T> createResVal(RetCode result_code, T&& value) {
    return ResValT<T>(result_code, std::forward<T>(value));
}

}// namespace taixu
