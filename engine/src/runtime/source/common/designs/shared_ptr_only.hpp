/**
 * @file shared_ptr_only.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "common/hal/tx_allocator.hpp"

namespace taixu {
/**
 * @brief only can use in shared_ptr, only can construct by shared_ptr.
 *
 * @tparam T child class type
 */
template<typename T>
class SharedPtrOnly : std::enable_shared_from_this<T> {
private:
    SharedPtrOnly<T>() = default;

public:
    template<typename... ArgsT>
    static std::shared_ptr<T> create(ArgsT&&... args) {
        std::shared_ptr<T> ptr{txAllocatorT<T>::allocate(1)};
        txAllocatorT<T>::construct(ptr.get(), std::forward<ArgsT>(args)...);
        return ptr;
    }
};
}// namespace taixu
