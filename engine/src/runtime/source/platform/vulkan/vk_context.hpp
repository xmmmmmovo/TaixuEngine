/**
 * @file vk_context.hpp
 * @author xmmmmmovo
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "management/gfx/tx_context.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/base/result.hpp"

TX_NAMESPACE_BEGIN

class VKContext final : public TXContext {
private:
    vk::raii::Instance               _instance{VK_NULL_HANDLE};
    vk::raii::DebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE};
    vk::raii::SurfaceKHR             _surface{VK_NULL_HANDLE};

    vk::raii::Device         _device{VK_NULL_HANDLE};
    vk::raii::PhysicalDevice _physical_device{VK_NULL_HANDLE};
    std::uint32_t            _graphicsFamilyIndex{0};

    vk::raii::Queue _graphics_queue{VK_NULL_HANDLE};

public:
    static ResValT<std::unique_ptr<VKContext>> createVulkanContext(const Window* window);
};

TX_NAMESPACE_END
