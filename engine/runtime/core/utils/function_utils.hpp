//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_FUNCTION_UTILS_HPP
#define TAIXUENGINE_FUNCTION_UTILS_HPP

#define INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(func) [this]() { func(); }
#define INCLASS_ARGS_FUNCTION_LAMBDA_WRAPPER(func) \
    (args)[this, &](args) { func(args); }

namespace taixu {
template<typename... Args>
using callback = std::function<void(Args...)>;//callback function
}// namespace taixu

#endif//TAIXUENGINE_FUNCTION_UTILS_HPP
