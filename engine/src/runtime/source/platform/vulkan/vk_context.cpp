/**
 * @file vk_context.cpp
 * @author xmmmmmovo
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_context.hpp"

#include "common/hal/tx_container.hpp"

#include "common/log/custom_fmt.hpp"
#include "taixu/common/base/lib_info.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"


#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>

#include "gameplay/gui/glfw_window.hpp"


/**
 * @brief Globale dynamic dispatch loader, only need write once
 */
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE


TX_NAMESPACE_BEGIN

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
    return UNEXPECTED(RetCode::UNIMPL_ERROR);
}

ResValT<TXDevice> createTXDevice(vk::raii::Instance const& instance, vk::raii::SurfaceKHR const& surface) {
    auto device = selectDevice(instance, surface);

    if (!device.has_value()) {
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }


    return {};
}

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

ResValT<std::unique_ptr<VKContext>> createVulkanContext(const Window* window) {
    initDynamicDispatchLoader();

    if (!window) {
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

    VkGlfwExtensions glfwexts = GLFWWindow::getVulkanInstanceExtensions();
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

    if (auto const res = glfwCreateWindowSurface(instance_c_ptr, static_cast<const GLFWWindow*>(window)->getRawWindow(),
                                                 nullptr, &surface_strct);
        res != VK_SUCCESS) {
        ERROR_LOG("Failed to create window surface: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    vk::raii::SurfaceKHR surface{instance.value(), surface_strct};

    auto physical_devices = createTXDevice(instance.value(), surface);

    return {};
}

TX_NAMESPACE_END
