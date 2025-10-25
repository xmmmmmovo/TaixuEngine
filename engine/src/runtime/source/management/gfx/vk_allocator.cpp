/**
 * @file vk_allocator.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-21
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_allocator.hpp"
#include "taixu/common/log/logger.hpp"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan_hpp_macros.hpp>

#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

TX_NAMESPACE_BEGIN

ResValT<VulkanAllocator> VulkanAllocator::createAllocator(vk::raii::PhysicalDevice& physical_device,
                                                          vk::raii::Device&         device,
                                                          vk::raii::Instance const& instance) {
    auto        props = physical_device.getProperties();
    const auto& d     = VULKAN_HPP_DEFAULT_DISPATCHER;

    VmaVulkanFunctions functions{};
    functions.vkGetInstanceProcAddr = d.vkGetInstanceProcAddr;
    functions.vkGetDeviceProcAddr   = d.vkGetDeviceProcAddr;

    VmaAllocatorCreateInfo create_info{};
    create_info.vulkanApiVersion = props.apiVersion;
    create_info.physicalDevice   = *physical_device;
    create_info.device           = *device;
    create_info.instance         = *instance;
    create_info.pVulkanFunctions = &functions;

    VmaAllocator allocator = VK_NULL_HANDLE;
    auto         res       = vmaCreateAllocator(&create_info, &allocator);
    if (res != VK_SUCCESS) {
        ERROR_LOG("Failed to create VMA allocator: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VMA_CREATE_FAILED_ERROR);
    }

    return VulkanAllocator(allocator);
}

TX_NAMESPACE_END
