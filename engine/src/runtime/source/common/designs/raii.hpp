/**
 * @file object.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <expected>
#include <memory>

#include "common/base/macro.hpp"
#include "common/hal/tx_allocator.hpp"

namespace taixu {

template<typename T, typename... Args, typename Deleter = std::default_delete<T>>
std::unique_ptr<T> create_unique_ptr(Args&&... args) {
    std::unique_ptr<T, Deleter> obj(txAllocatorT<T>::alloc(1));
    txAllocatorT<T>::construct(obj.get(), std::forward<Args>(args)...);
    TX_ASSERT(obj != nullptr);
    return obj;
}

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
