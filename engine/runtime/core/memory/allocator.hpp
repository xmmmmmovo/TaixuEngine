//
// Created by xmmmmmovo on 2023/4/25.
//

#ifndef TAIXUENGINE_ALLOCATOR_HPP
#define TAIXUENGINE_ALLOCATOR_HPP

#include <memory>
namespace taixu {

template<typename T>
class TXAllocator : public std::allocator<T> {};

}// namespace taixu

#endif//TAIXUENGINE_ALLOCATOR_HPP
