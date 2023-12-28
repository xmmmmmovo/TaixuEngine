//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_ALLOCATOR_HPP
#define TAIXUENGINE_ALLOCATOR_HPP

#include <memory>

#include "tx_memory_resource.hpp"

namespace taixu {

template<typename T, typename MemRes>
class TXAllocator : public std::allocator<T> {
    using value_type = T;
};

}// namespace taixu

#endif// TAIXUENGINE_ALLOCATOR_HPP
