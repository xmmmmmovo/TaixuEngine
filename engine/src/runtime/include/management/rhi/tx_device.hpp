/**
 * @file tx_device.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "common/designs/noncopyable.hpp"
namespace taixu {

class TXDevice final : private Noncopyable {
    vk::Device         _device{VK_NULL_HANDLE};
    vk::PhysicalDevice _physical_device{VK_NULL_HANDLE};
    vk::Queue          _graphics_queue{VK_NULL_HANDLE};

    
};

}// namespace taixu
