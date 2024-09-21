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

#include "taixu/common/log/logger.hpp"

namespace taixu {

tx_unordered_set<tx_string> getDeviceExtensions(vk::raii::PhysicalDevice const& physical_device) {
    auto const exts  = physical_device.enumerateDeviceExtensionProperties();
    auto       cview = exts | std::views::transform([](vk::ExtensionProperties const& prop) {
                     return tx_string{prop.extensionName.data()};
                 });
    return {cview.begin(), cview.end()};
}

/**
 * @brief get driver version string
 * @see
 * https://github.com/SaschaWillems/vulkan.gpuinfo.org/blob/1e6ca6e3c0763daabd6a101b860ab4354a07f5d3/functions.php#L294
 */
tx_string getDriverVersionStr(uint32_t vendorID, uint32_t driverVersion) {
    tx_ostringstream oss;

    if (4318 /* NVIDIA*/ == vendorID) {
        oss << ((driverVersion >> 22) & 0x3ff) << "." << ((driverVersion >> 14) & 0xff) << "."
            << ((driverVersion >> 6) & 0xff) << "." << (driverVersion & 0x3f);
    }
#if defined(TX_WINDOWS)// Windows only
    else if (0x8086 /* Intel, obviously */ == vendorID) {
        oss << (driverVersion >> 14) << "." << (driverVersion & 0x3fff);
    }
#endif// ~ Windows only
    else {
        // (Old) Vulkan convention, prior to the introduction of the
        // VK_API_VERSION_VARIANT bits at the top.
        oss << (driverVersion >> 22) << "." << ((driverVersion >> 12) & 0x3ff) << "." << (driverVersion & 0xfff);
    }

    return oss.str();
}

float scoreDevice(vk::raii::PhysicalDevice const& device, vk::raii::SurfaceKHR const& surface) {
    vk::PhysicalDeviceProperties props = device.getProperties();

    uint32_t major = VK_API_VERSION_MAJOR(props.apiVersion);
    uint32_t minor = VK_API_VERSION_MINOR(props.apiVersion);
    uint32_t patch = VK_API_VERSION_PATCH(props.apiVersion);

    INFO_LOG("Find GPU: {}(Vulkan {}.{}.{});Driver: {};Type: {}", tx_string(props.deviceName.data()), major, minor,
             patch, getDriverVersionStr(props.vendorID, props.driverVersion), vk::to_string(props.deviceType));

    if (major < 1 || (major == 1 && minor < 2)) {
        INFO_LOG("Discarding device '{}': insufficient vulkan version", tx_string_view(props.deviceName.data()));
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
        INFO_LOG("Discarding device '{}': missing extension {}", tx_string(props.deviceName.data()),
                 VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        return -1.0f;
    }

    auto const queue_family_props = device.getQueueFamilyProperties();
    INFO_LOG("Queue family: {} families", queue_family_props.size());
    for (auto&& family : queue_family_props) {
        INFO_LOG("\t{} ({} queues)", vk::to_string(family.queueFlags), family.queueCount);
    }

    auto const mem_props = device.getMemoryProperties();
    INFO_LOG("Memory: {} heaps", mem_props.memoryHeapCount);
    for (size_t i = 0; i < mem_props.memoryHeapCount; i++) {
        INFO_LOG("\tHeap {}: {} ({} MBytes)", i, vk::to_string(mem_props.memoryHeaps[i].flags),
                 (mem_props.memoryHeaps[i].size) / 1024 / 1024);
    }

    INFO_LOG("Memory: {} types", mem_props.memoryHeapCount);
    for (size_t i = 0; i < mem_props.memoryHeapCount; i++) {
        INFO_LOG("\tType {}: {} (heap {})", i, vk::to_string(mem_props.memoryTypes[i].propertyFlags),
                 mem_props.memoryTypes[i].heapIndex);
    }

    static constexpr vk::QueueFlags REQUIRED_QUEUE_FLAGS =
            vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute | vk::QueueFlagBits::eTransfer;

    for (size_t i = 0; i < queue_family_props.size(); i++) {
        if ((queue_family_props.at(i).queueCount > 0) && (queue_family_props.at(i).queueFlags & REQUIRED_QUEUE_FLAGS)) {
            if (auto const support = device.getSurfaceSupportKHR(i, *surface); !support) {
                INFO_LOG("Discarding device '{}': surface not supported", tx_string(props.deviceName.data()));
                return -1.f;
            }
        }
    }

    if (auto const features = device.getFeatures(); !features.samplerAnisotropy) {
        INFO_LOG("Discarding device '{}': samplerAnisotropy not supported", tx_string(props.deviceName.data()));
        return -1.f;
    }

    float score = 0.0f;
    if (props.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
        score += 500.0f;
    } else if (props.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) {
        score += 100.0f;
    }

    return score;
}

ResValT<vk::raii::PhysicalDevice> selectDevice(vk::raii::Instance const&   instance,
                                               vk::raii::SurfaceKHR const& surface) {
    auto devices = instance.enumeratePhysicalDevices();
    if (!devices.has_value()) {
        ERROR_LOG("Failed to enumerate physical devices: {}", vk::to_string(devices.error()));
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }

    float                    best_score = 0.0f;
    vk::raii::PhysicalDevice best_device{VK_NULL_HANDLE};

    for (auto const& device : devices.value()) {
        if (auto const score = scoreDevice(device, surface); score > best_score) {
            best_score  = score;
            best_device = device;
        }
    }

    return best_device;
}

ResValT<vk::raii::Device> createDevice(vk::raii::PhysicalDevice const& physical_device) {
    tx_vector<tx_string> enabled_dev_extensions{};

    enabled_dev_extensions.emplace_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

#if defined(TX_APPLE)
    enabled_dev_extensions.emplace_back("VK_KHR_portability_subset");
#endif

    INFO_LOG("Enabled device extensions: {}");


    tx_vector<uint32_t> queue_family_indices{};

    tx_vector<char const*> const enabled_dev_exts{};
    enabled_dev_extensions.emplace_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
#if defined(TX_APPLE)
    enabled_dev_exts.emplace_back("VK_KHR_portability_subset");
#endif
    INFO_LOG("Enabled device extensions:");
    for (auto const& ext : enabled_dev_extensions) {
        INFO_LOG("\t{}", ext);
    }
}

ResValT<TXDevice> createTXDevice(vk::raii::Instance const& instance, vk::raii::SurfaceKHR const& surface) {
    auto device = selectDevice(instance, surface);

    if (!device.has_value()) {
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }


    return {};
}

}// namespace taixu
