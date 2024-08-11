/**
 * @file tx_device.cpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-8
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#include "management/render/tx_device.hpp"

#include <vulkan/vk_enum_string_helper.h>

#include "common/log/logger.hpp"

namespace taixu {

tx_unordered_set<tx_string> getDeviceExtensions(vk::raii::PhysicalDevice const& physical_device) {
    auto const exts  = physical_device.enumerateDeviceExtensionProperties();
    auto       cview = exts | std::views::transform([](vk::ExtensionProperties const& prop) {
                     return tx_string{prop.extensionName.data()};
                 });
    return {cview.begin(), cview.end()};
}

float scoreDevice(vk::raii::PhysicalDevice const& device, VkSurfaceKHR surface) {
    vk::PhysicalDeviceProperties props = device.getProperties();

    uint32_t major = VK_API_VERSION_MAJOR(props.apiVersion);
    uint32_t minor = VK_API_VERSION_MINOR(props.apiVersion);

    if (major < 1 || (major == 1 && minor < 2)) {
        ERROR_LOG("Discarding device '{}': insufficient vulkan version",
                  tx_string_view(props.deviceName.data()));
        return -1.0f;
    }

    // additional checks
    //  - check that the VK_KHR_swapchain extension is supported
    //  - check that there is a queue family that can present to the
    //    given surface
    //  - check that there is a queue family that supports graphics
    //    commands
    auto const exts = getDeviceExtensions(device);
    if (!exts.contains(VK_KHR_SWAPCHAIN_EXTENSION_NAME)) {
        ERROR_LOG("Discarding device '{}': missing extension {}",
                  tx_string_view(props.deviceName.data()), VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        return -1.0f;
    }
}

ResValT<vk::raii::PhysicalDevice> selectDevice(vk::raii::Instance const& instance) {
    uint32_t deviceCount = 0;

    auto devices = instance.enumeratePhysicalDevices();
    if (!devices.has_value()) {
        ERROR_LOG("Failed to enumerate physical devices: {}", vk::to_string(devices.error()));
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }

    float                    best_score = 0.0f;
    vk::raii::PhysicalDevice best_device{VK_NULL_HANDLE};

    for (auto const& device : devices.value()) {
        // auto const score = scoreDevice(device, );
    }
}

ResValT<TXDevice> createTXDevice(vk::raii::Instance const& instance) {
    auto device = selectDevice(instance);

    return {};
}

}// namespace taixu
