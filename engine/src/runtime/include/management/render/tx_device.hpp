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

#include <vulkan/vulkan_raii.hpp>

#include "common/designs/noncopyable.hpp"

namespace taixu {

class TXDevice final : public Noncopyable {
    vk::raii::Device         _device{VK_NULL_HANDLE};
    vk::raii::PhysicalDevice _physical_device{VK_NULL_HANDLE};
    std::uint32_t            _graphicsFamilyIndex{0};

    vk::raii::Queue _graphics_queue{VK_NULL_HANDLE};
};

}// namespace taixu
