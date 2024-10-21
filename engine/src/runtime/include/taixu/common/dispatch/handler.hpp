//
// Created by xmmmmmovo on 3/2/2024.
//

#pragma once

#include <cassert>

#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

namespace taixu {

/**
 * 使用：
 * ```cpp
 * Handler hand{+[](int a, double b){}};
 * hand(1, 2);
 * ```
 * @brief Handler，用于回调和事件处理
 * @note 回调的返回值必须是void，参数类型可以任意
 * @note
 * 如果想传递lambda到构造函数中需要转换为函数指针，lambda前必须要加`+`运算符
 * @see
 * https://stackoverflow.com/questions/18889028/a-positive-lambda-what-sorcery-is-this
 */
struct Handler {
    void (*f)();
    const std::type_info& info;

    template<typename T>
    explicit Handler(T fn) : f(reinterpret_cast<void (*)()>(fn)), info(typeid(T)) {
    }

    template<typename... Args>
    void operator()(Args&&... args) {
        using Fn = void(Args...);
        TX_ASSERT_MSG(info.hash_code() == typeid(Fn*).hash_code(),
                      "Cannot invoke handle function because param not match.");
        return (reinterpret_cast<Fn*>(f))(std::forward<Args>(args)...);
    }
};

}// namespace taixu
