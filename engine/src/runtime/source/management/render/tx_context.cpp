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
#include "common/base/lib_info.hpp"
#include "common/base/macro.hpp"
#include "common/hal/tx_container.hpp"
#include "common/log/logger.hpp"

#define VOLK_IMPLEMENTATION
#include <volk.h>
#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>

namespace taixu {


ResValT<tx_unordered_set<const char*>> getInstanceSupportedLayers() {
    // Get Vulkan extensions and support layers
    const auto supported_layers =
            vk::enumerateInstanceLayerProperties<txAllocatorT<vk::LayerProperties>>();
    if (supported_layers.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan layers: {}", vk::to_string(supported_layers.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    tx_unordered_set<const char*> ret{};
    for (auto&& layer : supported_layers.value) {
        if (!ret.contains(layer.layerName.data())) { ret.emplace(layer.layerName.data()); }
    }

    return ret;
}

ResValT<tx_unordered_set<const char*>> getInstanceSupportedExtensions() {
    const auto supported_extensions = vk::enumerateInstanceExtensionProperties();
    if (supported_extensions.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan extensions: {}",
                  vk::to_string(supported_extensions.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    tx_unordered_set<const char*> ret{};
    for (auto&& extension : supported_extensions.value) {
        if (!ret.contains(extension.extensionName)) { ret.emplace(extension.extensionName); }
    }

    return ret;
}

ResValT<vk::raii::Instance>
createInstance(tx_vector<const char*> const&                               enabled_layers,
               tx_vector<const char*> const&                               enabled_extensions,
               std::optional<vk::DebugUtilsMessengerCreateInfoEXT&> const& info) {
    vk::ApplicationInfo app_info{
            LIB_INFO.name.data(), LIB_INFO.version,   LIB_INFO.name.data(),
            LIB_INFO.version,     VK_API_VERSION_1_3,
    };

    const vk::InstanceCreateInfo create_info{vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
                                             &app_info,
                                             static_cast<uint32_t>(enabled_layers.size()),
                                             enabled_layers.data(),
                                             static_cast<uint32_t>(enabled_extensions.size()),
                                             enabled_extensions.data(),
                                             info.has_value() ? &info.value() : nullptr};

    // TODO: check why have this line below
    if (info.has_value()) { info.value().pNext = &create_info; }

    const auto instance = vk::createInstance(create_info);

    if (instance.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to create Vulkan instance: {}", vk::to_string(instance.result));
        return UNEXPECTED(RetCode::VULKAN_INSTANCE_CREATE_ERROR);
    }

    volkLoadInstance(instance.value);

    return vk::raii::Instance{vk::raii::Context{}, instance.value};
}

ResValT<std::unique_ptr<TXContext>> createTXContext(const Window* window) {
    if (auto const res = volkInitialize(); res != VK_SUCCESS) {
        ERROR_LOG("Failed to initialize volk: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }


    if (!window || !Window::isSupportVulkan()) {
        ERROR_LOG("Window is not support vulkan");
        return UNEXPECTED(RetCode::UNSUPPORTED_VULKAN_ERROR);
    }

    tx_vector<const char*> enabled_layers;
    tx_vector<const char*> enabled_extensions;

    auto supported_layers = getInstanceSupportedLayers();
    if (!supported_layers.has_value()) { return UNEXPECTED(supported_layers.error()); }

    auto supported_extensions = getInstanceSupportedExtensions();
    if (!supported_extensions.has_value()) { return UNEXPECTED(supported_extensions.error()); }

    bool enable_debug_utils = false;

#if defined(TX_DEBUG)
    #define DEBUG_LAYER_NAME "VK_LAYER_KHRONOS_validation"
    #define DEBUG_EXTENSION_NAME "VK_EXT_debug_utils"

    if (supported_layers.value().contains(DEBUG_LAYER_NAME) &&
        supported_extensions.value().contains(DEBUG_EXTENSION_NAME)) {

        enabled_layers.emplace_back(DEBUG_LAYER_NAME);
        enabled_extensions.emplace_back(DEBUG_EXTENSION_NAME);
        enable_debug_utils = true;
    }
#endif

#if defined(TX_APPLE)
    enabled_extensions.emplace_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    enabled_extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    VkGlfwExtensions glfwexts = Window::getVulkanInstanceExtensions();
    if (glfwexts.count == 0) {
        ERROR_LOG("Failed to get Vulkan extensions");
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    for (uint32_t i = 0; i < glfwexts.count; i++) {
        if (!supported_extensions.value().contains(glfwexts.names[i])) {
            ERROR_LOG("Failed to get GLFW needed Vulkan extensions: {}", glfwexts.names[i]);
            return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
        }
        enabled_extensions.emplace_back(glfwexts.names[i]);
    }

    vk::DebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info{};

    if (enable_debug_utils) {
        debug_utils_messenger_create_info.sType =
                vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
        debug_utils_messenger_create_info.messageSeverity =
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
        debug_utils_messenger_create_info.messageType =
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
        debug_utils_messenger_create_info.pfnUserCallback =
                [](VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                   VkDebugUtilsMessageTypeFlagsEXT             message_type,
                   VkDebugUtilsMessengerCallbackDataEXT const* p_callback_data, void*) -> VkBool32 {
            auto level = Logger::LogLevel::INFO;
            if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                level = Logger::LogLevel::INFO;
            } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                level = Logger::LogLevel::WARN;
            } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                level = Logger::LogLevel::ERR;
            }
            // use info warn error log by level variable
            Logger::log(LOG_SOURCE_LOC, level, "{}: {} ({})\n{}",
                        vk::to_string(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(message_type)),
                        p_callback_data->pMessageIdName, p_callback_data->messageIdNumber,
                        p_callback_data->pMessage);
            return vk::False;
        };
        debug_utils_messenger_create_info.pUserData = nullptr;
    }

    auto instance =
            createInstance(enabled_layers, enabled_extensions, debug_utils_messenger_create_info);

    if (!instance.has_value()) { return UNEXPECTED(instance.error()); }

    if (enable_debug_utils) {
        auto debug_utils_messenger = instance->createDebugUtilsMessengerEXT(
                debug_utils_messenger_create_info, nullptr, instance->getDispatcher());
        if (!debug_utils_messenger.has_value()) {
            ERROR_LOG("Failed to create debug utils messenger");
            return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
        }
    }

    return {};
}

}// namespace taixu
