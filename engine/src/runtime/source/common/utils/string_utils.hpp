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

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
