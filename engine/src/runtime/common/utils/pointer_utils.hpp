//
// Created by xmmmmmovo on 2023/7/25.
//

#ifndef ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP
#define ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP

#include "common/base/macro.hpp"

namespace taixu {

struct FreeDeleter {
    template<typename T>
    void operator()(T* ptr) const noexcept {
        if (ptr) { free(ptr); }
    }
};

template<typename T>
using free_unique_ptr = std::unique_ptr<T, FreeDeleter>;

template<typename T>
TX_INLINE free_unique_ptr<T> make_free_unique_ptr(T* ptr) {
    return free_unique_ptr<T>(ptr);
}

template<typename T>
TX_INLINE T* malloc_bytes(std::size_t size) noexcept {
    return reinterpret_cast<T*>(malloc(size));
}

}// namespace taixu

#endif// ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP
