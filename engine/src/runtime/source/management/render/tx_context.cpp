/**
 * @file tx_context.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <optional>

#include "common/log/logger.hpp"
#include "management/render/tx_context.hpp"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan_static_assertions.hpp>

namespace taixu {

std::optional<TXContext> createContext(Window* window) {
    if (auto const res = volkInitialize(); res != VK_SUCCESS) {
        FATAL_LOG("Failed to initialize volk: {}", string_VkResult(res));
        return std::nullopt;
    }

    if (!window || !Window::isSupportVulkan()) {
        FATAL_LOG("Window is not support vulkan");
        return std::nullopt;
    }

    // Get Vulkan extensions and support layers
    auto layers = vk::enumerateInstanceLayerProperties();
    if (layers.result != vk::Result::eSuccess) {
        FATAL_LOG("Failed to get Vulkan layers: {}", vk::to_string(layers.result));
        return std::nullopt;
    }

    auto extensions = vk::enumerateInstanceExtensionProperties(nullptr);


    VkGlfwExtensions exts = Window::getVulkanInstanceExtensions();
    if (exts.count == 0) {
        FATAL_LOG("Failed to get Vulkan extensions");
        return std::nullopt;
    }

    return {};
}

}// namespace taixu
