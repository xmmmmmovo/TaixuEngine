/**
 * @file vk_utils.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-10-27
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/macro.hpp"

#include <vulkan/vulkan_enums.hpp>
#include <vulkan/vulkan_to_string.hpp>

/**
 *  FUCK OFF BULLSHIT MSVC.
 *  FUCK OFF BULLSHIT MSVC.
 *  FUCK OFF BULLSHIT MSVC.
 */
#if defined(TX_MSVC) && defined(MemoryBarrier)
    #undef MemoryBarrier
#endif

TX_NAMESPACE_BEGIN

// define concept vk type that can use in vk::to_string
template<typename T>
concept VKStringable = requires(T t) { vk::to_string(t); };

/**
 * @brief get the queue family index
 *
 * @param device
 * @param surface
 * @param props
 * @param flags
 * @return std::optional<uint32_t>
 */
std::optional<uint32_t> findQueueFamily(vk::raii::PhysicalDevice const& device, vk::raii::SurfaceKHR const& surface,
                                        std::vector<vk::QueueFamilyProperties> const& props,
                                        std::optional<vk::QueueFlagBits>              flag_opt) noexcept;

/**
 * @brief Create a Command Pool object
 *
 * @param device
 * @param queue_family_index
 * @param flags
 * @return vk::raii::CommandPool
 */
vk::raii::CommandPool createCommandPool(vk::raii::Device const& device, uint32_t queue_family_index,
                                        vk::CommandPoolCreateFlags flags) noexcept;

/**
 * @brief Create a Fence object
 *
 * @param device
 * @param flags
 * @return vk::raii::Fence
 */
vk::raii::Fence createFence(vk::raii::Device const& device, vk::FenceCreateFlags flags) noexcept;

/**
 * @brief Create a Semaphore object
 *
 * @param device
 * @return vk::raii::Semaphore
 */
vk::raii::Semaphore createSemaphore(vk::raii::Device const& device) noexcept;

/// TODO: Below are not finished.
vk::MemoryBarrier getVKMemoryBarrier(vk::AccessFlags src_access_mask, vk::AccessFlags dst_access_mask) noexcept;

vk::ImageMemoryBarrier getVulkanImageMemoryBarrier(vk::AccessFlags src_access_mask,
                                                   vk::AccessFlags dst_access_mask) noexcept;

TX_NAMESPACE_END
