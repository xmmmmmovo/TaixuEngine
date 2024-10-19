/**
 * @file tx_device.hpp
 * @author xmmmmmovo
 * @date 2024-07-12
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <vulkan/vulkan_raii.hpp>

#include "taixu/common/base/result.hpp"
#include "taixu/common/designs/noncopyable.hpp"

#include "common/hal/tx_container.hpp"
#include "common/hal/tx_string.hpp"

namespace taixu {

class TXDevice final : public Noncopyable {
    vk::raii::Device         _device{VK_NULL_HANDLE};
    vk::raii::PhysicalDevice _physical_device{VK_NULL_HANDLE};
    std::uint32_t            _graphicsFamilyIndex{0};

    vk::raii::Queue _graphics_queue{VK_NULL_HANDLE};
};

tx_unordered_set<tx_string> getDeviceExtensions(vk::raii::PhysicalDevice const& physical_device);

ResValT<TXDevice> createTXDevice(vk::raii::Instance const& instance, vk::raii::SurfaceKHR const& surface);

}// namespace taixu
