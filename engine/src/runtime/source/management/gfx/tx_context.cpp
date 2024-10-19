/**
 * @file tx_context.cpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "management/gfx/tx_context.hpp"
#include "common/hal/tx_container.hpp"

#include "taixu/common/base/lib_info.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>

/**
 * @brief Globale dynamic dispatch loader, only need write once
 */
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace taixu {

ResValT<tx_unordered_set<tx_string>> getInstanceSupportedLayers() {
    // Get Vulkan extensions and support layers
    const auto supported_layers = vk::enumerateInstanceLayerProperties<txAllocatorT<vk::LayerProperties>>();
    if (supported_layers.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan layers: {}", vk::to_string(supported_layers.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    tx_unordered_set<tx_string> ret{};
    for (auto&& layer : supported_layers.value) {
        if (auto str_name = tx_string{layer.layerName.data()}; !ret.contains(str_name)) {
            ret.emplace(std::move(str_name));
        }
    }

    return ret;
}

ResValT<tx_unordered_set<tx_string>> getInstanceSupportedExtensions() {
    const auto supported_extensions = vk::enumerateInstanceExtensionProperties();
    if (supported_extensions.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to get Vulkan extensions: {}", vk::to_string(supported_extensions.result));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    tx_unordered_set<tx_string> ret{};
    for (auto&& extension : supported_extensions.value) {
        if (auto str_name = tx_string{extension.extensionName.data()}; !ret.contains(str_name)) {
            ret.emplace(std::move(str_name));
        }
    }

    return ret;
}

ResValT<vk::raii::Instance> createInstance(tx_vector<const char*> const&                        enabled_layers,
                                           tx_vector<const char*> const&                        enabled_extensions,
                                           std::optional<vk::DebugUtilsMessengerCreateInfoEXT>& debug_info) {
    // Log layers and extensions
    for (auto&& layer : enabled_layers) {
        INFO_LOG("Enabled layer: {}", layer);
    }
    for (auto&& extension : enabled_extensions) {
        INFO_LOG("Enabled extension: {}", extension);
    }

    vk::ApplicationInfo app_info{
            LIB_INFO.name.data(), LIB_INFO.version, LIB_INFO.name.data(), LIB_INFO.version, VK_API_VERSION_1_3,
    };

    const vk::InstanceCreateInfo create_info{{},
                                             &app_info,
                                             static_cast<uint32_t>(enabled_layers.size()),
                                             enabled_layers.data(),
                                             static_cast<uint32_t>(enabled_extensions.size()),
                                             enabled_extensions.data(),
                                             debug_info.has_value() ? &debug_info.value() : nullptr};

    const auto instance = vk::createInstance(create_info);

    if (instance.result != vk::Result::eSuccess) {
        ERROR_LOG("Failed to create Vulkan instance: {}", vk::to_string(instance.result));
        return UNEXPECTED(RetCode::VULKAN_INSTANCE_CREATE_ERROR);
    }

    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.value);

    return vk::raii::Instance{vk::raii::Context{}, instance.value};
}

void initDynamicDispatchLoader() {
    // initialize minimal set of function pointers
    VULKAN_HPP_DEFAULT_DISPATCHER.init();

    // the same initialization, now with explicitly providing a DynamicLoader
    vk::DynamicLoader dl;
    VULKAN_HPP_DEFAULT_DISPATCHER.init(dl);

    // the same initialization, now with explicitly providing the initial function pointer
    PFN_vkGetInstanceProcAddr getInstanceProcAddr =
            dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(getInstanceProcAddr);
}

ResValT<std::unique_ptr<TXContext>> createTXContext(const Window* window) {
    initDynamicDispatchLoader();

    if (!window || !Window::isSupportVulkan()) {
        ERROR_LOG("Window is not support vulkan");
        return UNEXPECTED(RetCode::UNSUPPORTED_VULKAN_ERROR);
    }

    tx_vector<const char*> enabled_layers;
    tx_vector<const char*> enabled_extensions;

    auto supported_layers = getInstanceSupportedLayers();
    if (!supported_layers.has_value()) {
        return UNEXPECTED(supported_layers.error());
    }

    auto supported_extensions = getInstanceSupportedExtensions();
    if (!supported_extensions.has_value()) {
        return UNEXPECTED(supported_extensions.error());
    }

    bool enable_debug_utils = false;

#if defined(TX_DEBUG)
    #define DEBUG_LAYER_NAME "VK_LAYER_KHRONOS_validation"
    #define DEBUG_EXTENSION_NAME "VK_EXT_debug_utils"

    if (supported_layers.value().contains(tx_string(DEBUG_LAYER_NAME)) &&
        supported_extensions.value().contains(tx_string(DEBUG_EXTENSION_NAME))) {

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

    std::optional<vk::DebugUtilsMessengerCreateInfoEXT> debug_utils_messenger_create_info_opt{std::nullopt};

    if (enable_debug_utils) {
        vk::DebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info{};
        debug_utils_messenger_create_info.sType           = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
        debug_utils_messenger_create_info.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                                                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                                                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
        debug_utils_messenger_create_info.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                                                        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                                                        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
        debug_utils_messenger_create_info.pfnUserCallback =
                [](VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                   VkDebugUtilsMessageTypeFlagsEXT             message_type,
                   VkDebugUtilsMessengerCallbackDataEXT const* p_callback_data, void*) -> VkBool32 {
            auto level = Logger::LogLevel::DEBUG;
            if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
                level = Logger::LogLevel::DEBUG;
            } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                level = Logger::LogLevel::WARN;
            } else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                level = Logger::LogLevel::ERR;
            }
            // use info warn error log by level variable
            Logger::log(LOG_SOURCE_LOC, level, "{}: {} ({})\n\t{}",
                        vk::to_string(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(message_type)),
                        p_callback_data->pMessageIdName, p_callback_data->messageIdNumber, p_callback_data->pMessage);
            return vk::False;
        };
        debug_utils_messenger_create_info.pUserData = nullptr;

        debug_utils_messenger_create_info_opt = debug_utils_messenger_create_info;
    }

    auto instance = createInstance(enabled_layers, enabled_extensions, debug_utils_messenger_create_info_opt);

    if (!instance.has_value()) {
        return UNEXPECTED(instance.error());
    }

    vk::raii::DebugUtilsMessengerEXT debug_messenger{VK_NULL_HANDLE};
    if (enable_debug_utils) {
        auto debug_messenger_expt =
                instance->createDebugUtilsMessengerEXT(debug_utils_messenger_create_info_opt.value());
        if (!debug_messenger_expt.has_value()) {
            ERROR_LOG("Failed to create debug utils messenger: {}", vk::to_string(debug_messenger_expt.error()));
            return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
        }
        debug_messenger = std::move(debug_messenger_expt.value());
    }

    VkSurfaceKHR surface_strct{VK_NULL_HANDLE};
    VkInstance   instance_c_ptr = *(instance.value());

    if (auto const res = glfwCreateWindowSurface(instance_c_ptr, window->getRawWindow(), nullptr, &surface_strct);
        res != VK_SUCCESS) {
        ERROR_LOG("Failed to create window surface: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    vk::raii::SurfaceKHR surface{instance.value(), surface_strct};

    auto physical_devices = createTXDevice(instance.value(), surface);

    return {};
}

}// namespace taixu
