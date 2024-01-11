//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_FUNCTION_UTILS_HPP
#define TAIXUENGINE_FUNCTION_UTILS_HPP

#define INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(func) [this]() { func(); }
#define INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(func)                              \
    [this](std::string_view const& str_view) { func(str_view); }

#include <functional>

namespace taixu {
template<typename... Args>
using callback = std::function<void(Args...)>;// callback function
}// namespace taixu

#endif// TAIXUENGINE_FUNCTION_UTILS_HPP
