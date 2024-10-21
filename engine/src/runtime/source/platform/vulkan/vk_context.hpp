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

TX_NAMESPACE_BEGIN

class VKContext final : public TXContext {
public:
    vk::raii::Instance               _instance{VK_NULL_HANDLE};
    vk::raii::DebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE};
    vk::raii::SurfaceKHR             _surface{VK_NULL_HANDLE};

    vk::raii::Device         _device{VK_NULL_HANDLE};
    vk::raii::PhysicalDevice _physical_device{VK_NULL_HANDLE};
    std::uint32_t            _graphicsFamilyIndex{0};

    vk::raii::Queue _graphics_queue{VK_NULL_HANDLE};
};

tx_unordered_set<tx_string> getDeviceExtensions(vk::raii::PhysicalDevice const& physical_device);

ResValT<TXDevice> createTXDevice(vk::raii::Instance const& instance, vk::raii::SurfaceKHR const& surface);


/**
 *
 * @return get all supported layers and unique them to unordered_set
 */
ResValT<tx_unordered_set<tx_string>> getInstanceSupportedLayers();

/**
 *
 * @return get all supported extensions and unique them to unordered_set
 */
ResValT<tx_unordered_set<tx_string>> getInstanceSupportedExtensions();


ResValT<vk::raii::Instance> createInstance(tx_vector<const char*> const&                        enabled_layers,
                                           tx_vector<const char*> const&                        enabled_extensions,
                                           std::optional<vk::DebugUtilsMessengerCreateInfoEXT>& info);

ResValT<std::unique_ptr<TXContext>> createTXContext(const Window* window);

ResValT<std::unique_ptr<VKContext>> createVulkanContext(const Window* window);

TX_NAMESPACE_END
