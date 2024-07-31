//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
#define ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2


#include <string>

#include "common/hal/tx_string.hpp"

namespace taixu {

/**
 * @brief Convert a wide Unicode string to an UTF8 string
 *
 * @param wstr
 * @return tx_string
 */
tx_string utf8Encode(const tx_wstring& wstr);

/**
 * @brief Convert an UTF8 string to a wide Unicode String
 *
 * @param str
 * @return tx_wstring
 */
tx_wstring utf8Decode(const tx_string& str);

/**
 * @brief string verion to uint32_t version. eg.: "1.0.0" -> (major, minor, patch)
 *
 * @param version
 * @return uint32_t
 */
constexpr uint32_t str2uint32Version(tx_string_view version) {
    std::array<uint32_t, 3> ver_arr{0, 0, 0};
    uint8_t                 idx = 0;

    constexpr uint8_t SHIFT       = 10;
    constexpr uint8_t MAJOR_SHIFT = 22;
    constexpr uint8_t MINOR_SHIFT = 12;

    for (auto c : version) {
        if (c == '.') {
            assert((idx < 3) && "version string is invalid");
            idx++;
            continue;
        }
        ver_arr.at(idx) = ver_arr.at(idx) * SHIFT + (c - '0');
    }
    return (ver_arr[0] << MAJOR_SHIFT) | (ver_arr[1] << MINOR_SHIFT) | (ver_arr[2]);
}


}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
