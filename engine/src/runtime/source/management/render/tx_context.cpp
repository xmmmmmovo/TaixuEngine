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

#include "management/render/tx_context.hpp"
#include "common/base/macro.hpp"
#include "common/log/logger.hpp"

#define VOLK_IMPLEMENTATION
#include <volk.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_static_assertions.hpp>

namespace taixu {

vk::raii::Instance createInstance() { return nullptr; }

ResValT<TXContext> createTXContext(Window* window) {
    if (auto const res = volkInitialize(); res != VK_SUCCESS) {
        ERROR_LOG("Failed to initialize volk: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }


    if (!window || !Window::isSupportVulkan()) {
        ERROR_LOG("Window is not support vulkan");
        return UNEXPECTED(RetCode::UNSUPPORTED_VULKAN_ERROR);
    }

    // Get Vulkan extensions and support layers
    auto layers = vk::enumerateInstanceLayerProperties();
    if (layers.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan layers: {}", vk::to_string(layers.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    auto extensions = vk::enumerateInstanceExtensionProperties();
    if (extensions.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan extensions: {}", vk::to_string(extensions.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    bool enable_debug_utils = false;

#if !defined(TX_DEBUG)

#endif

    VkGlfwExtensions exts = Window::getVulkanInstanceExtensions();
    if (exts.count == 0) {
        ERROR_LOG("Failed to get Vulkan extensions");
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    return {};
}

}// namespace taixu
