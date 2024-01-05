//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
#define ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2

#include "common/base/macro.hpp"

#include <string>

#ifdef TX_WINDOWS
    #include "platform/os/windows/windows_headers.hpp"
    #include <stringapiset.h>
#endif

namespace taixu {

// Convert a wide Unicode string to an UTF8 string
TX_INLINE std::string utf8Encode(const std::wstring& wstr) {
    std::string res;
#ifdef TX_WINDOWS
    if (!wstr.empty()) {
        int size_needed = WideCharToMultiByte(
                CP_UTF8, 0, &wstr[0], (int) wstr.size(), NULL, 0, NULL, NULL);
        if (size_needed) {
            res = std::string(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int) wstr.size(),
                                &res[0], size_needed, NULL, NULL);
        }
    }
#else
    // Suppress warnings from the compiler.
    (void) wstr;
#endif// TX_WINDOWS
    return res;
}

// Convert an UTF8 string to a wide Unicode String
TX_INLINE std::wstring utf8Decode(const std::string& str) {
    std::wstring res;
#ifdef TX_WINDOWS
    if (!str.empty()) {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0],
                                              (int) str.size(), NULL, 0);
        if (size_needed) {
            res = std::wstring(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int) str.size(), &res[0],
                                size_needed);
        }
    }
#else
    // Suppress warnings from the compiler.
    (void) str;
#endif// TX_WINDOWS
    return res;
}

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_COMMON_UTILS_STRING_UTILS_FB46C8C838AD48F8AE45DB0825E835F2
