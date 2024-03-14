//
// Created by xmmmmmovo on 1/19/2024.
//

#include "string_utils.hpp"

#include "common/base/macro.hpp"

#ifdef TX_WINDOWS
    #include "platform/windows/windows_min.hpp"
    #include <stringapiset.h>
#endif

namespace taixu {

std::string utf8Encode(const std::wstring& wstr) {
    std::string res;
#ifdef TX_WINDOWS
    if (!wstr.empty()) {
        if (const int size_needed = WideCharToMultiByte(
                    CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()),
                    nullptr, 0, nullptr, NULL)) {
            res = std::string(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, &wstr[0],
                                static_cast<int>(wstr.size()), &res[0],
                                size_needed, nullptr, NULL);
        }
    }
#else
    // Suppress warnings from the compiler.
    (void) wstr;
#endif// TX_WINDOWS
    return res;
}

std::wstring utf8Decode(const std::string& str) {
    std::wstring res;
#ifdef TX_WINDOWS
    if (!str.empty()) {
        if (const int size_needed = MultiByteToWideChar(
                    CP_UTF8, 0, &str[0], static_cast<int>(str.size()), NULL,
                    0)) {
            res = std::wstring(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0],
                                static_cast<int>(str.size()), &res[0],
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