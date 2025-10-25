/**
 * @file vk_utils.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-10-27
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_utils.hpp"
#include "taixu/common/log/logger.hpp"

TX_NAMESPACE_BEGIN

std::optional<uint32_t> findQueueFamily(vk::raii::PhysicalDevice const& device, vk::raii::SurfaceKHR const& surface,
                                        std::vector<vk::QueueFamilyProperties> const& props,
                                        std::optional<vk::QueueFlagBits>              flag_opt) noexcept {
    static constexpr vk::QueueFlags REQUIRED_QUEUE_FLAGS = vk::QueueFlagBits::eGraphics;

    auto flags = flag_opt.value();

    for (uint32_t i = 0; i < props.size(); i++) {
        auto& prop = props.at(i);
        if ((prop.queueCount > 0) && (!flag_opt.has_value() || (flags == (prop.queueFlags & flags)))) {
            if (flag_opt.has_value() && (flags & REQUIRED_QUEUE_FLAGS)) {
                if (const VkBool32 supported = device.getSurfaceSupportKHR(i, *surface); supported) {
                    return i;
                }
            } else {
                return i;
            }
        }
    }

    return std::nullopt;
}

vk::raii::CommandPool createCommandPool(vk::raii::Device const& device, uint32_t queue_family_index,
                                        vk::CommandPoolCreateFlags flags) noexcept {

    vk::CommandPoolCreateInfo command_pool_info{};
    command_pool_info.setQueueFamilyIndex(queue_family_index).setFlags(flags);

    auto ret = device.createCommandPool(command_pool_info);
    if (!ret.has_value()) {
        ERROR_LOG("create command pool failed: {}", vk::to_string(ret.error()));
        return VK_NULL_HANDLE;
    }

    return std::move(ret.value());
}


vk::raii::Fence createFence(vk::raii::Device const& device, vk::FenceCreateFlags flags) noexcept {
    vk::FenceCreateInfo fence_info{};
    fence_info.setFlags(flags);

    auto ret = device.createFence(fence_info);
    if (!ret.has_value()) {
        ERROR_LOG("create fence failed: {}", vk::to_string(ret.error()));
        return VK_NULL_HANDLE;
    }

    return std::move(ret.value());
}


vk::raii::Semaphore createSemaphore(vk::raii::Device const& device) noexcept {
    vk::SemaphoreCreateInfo create_info{};

    auto ret = device.createSemaphore(create_info);
    if (!ret.has_value()) {
        ERROR_LOG("create semaphore failed: {}", vk::to_string(ret.error()));
        return VK_NULL_HANDLE;
    }

    return std::move(ret.value());
}


vk::MemoryBarrier getVKMemoryBarrier(vk::AccessFlags src_access_mask, vk::AccessFlags dst_access_mask) noexcept {
    return {};
}


vk::ImageMemoryBarrier getVulkanImageMemoryBarrier(vk::AccessFlags src_access_mask,
                                                   vk::AccessFlags dst_access_mask) noexcept {
    return {};
}


TX_NAMESPACE_END
