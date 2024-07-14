/**
 * @file tx_allocator.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <mimalloc-new-delete.h>
#include <mimalloc-override.h>

namespace taixu {

template<typename T>
using txAllocatorT = mi_stl_allocator<T>;

}// namespace taixu
