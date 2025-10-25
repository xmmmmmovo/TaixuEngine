/**
 * @file tx_vk_allocator.hpp
 * @author xmmmmmovo
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/macro.hpp"
#include "taixu/common/base/result.hpp"
#include "taixu/common/designs/noncopyable.hpp"

#include <vk_mem_alloc.h>

TX_NAMESPACE_BEGIN

class VulkanAllocator final : public Noncopyable {
public:
    VulkanAllocator() = default;

    explicit VulkanAllocator(VmaAllocator allocator) : _allocator(allocator) {
    }

    VulkanAllocator(const VulkanAllocator&)            = delete;
    VulkanAllocator& operator=(const VulkanAllocator&) = delete;

    VulkanAllocator(VulkanAllocator&& other) noexcept : _allocator(std::exchange(other._allocator, VK_NULL_HANDLE)) {};
    VulkanAllocator& operator=(VulkanAllocator&& other) noexcept {
        std::swap(_allocator, other._allocator);
        return *this;
    };

    ~VulkanAllocator() override {
        vmaDestroyAllocator(_allocator);
    }

    static ResValT<VulkanAllocator> createAllocator(vk::raii::PhysicalDevice& physical_device, vk::raii::Device& device,
                                                    vk::raii::Instance const& instance);

private:
    VmaAllocator _allocator{VK_NULL_HANDLE};
};


TX_NAMESPACE_END
