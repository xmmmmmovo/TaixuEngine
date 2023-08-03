//
// Created by xmmmmmovo on 2023/7/25.
//

#ifndef ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP
#define ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP

namespace taixu {

struct FreeDeleter {
    template<typename T>
    void operator()(T* ptr) const noexcept {
        if (ptr) { free(ptr); }
    }
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_UTILS_POINTER_UTILS_HPP
