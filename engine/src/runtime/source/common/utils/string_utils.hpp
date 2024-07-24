//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
#define ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2


#include <string>

namespace taixu {

// Convert a wide Unicode string to an UTF8 string
std::string utf8Encode(const std::wstring& wstr);

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8Decode(const std::string& str);

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
