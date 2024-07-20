/**
 * @file object.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "common/base/macro.hpp"
#include "common/hal/tx_allocator.hpp"

namespace taixu {

template<typename T, typename... Args, typename Deleter>
std::unique_ptr<T> create_unique_ptr(Args&&... args) {
    std::unique_ptr<T> obj(txAllocatorT<T>::alloc(1));
    txAllocatorT<T>::construct(obj.get(), std::forward<Args>(args)...);
    TX_ASSERT(obj != nullptr);
    return obj;
}

}// namespace taixu
