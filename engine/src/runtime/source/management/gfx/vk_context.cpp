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
#include "common/hal/tx_string.hpp"
#include "common/log/custom_fmt.hpp"
#include "gameplay/gui/glfw_window.hpp"
#include "taixu/common/base/lib_info.hpp"
#include "taixu/common/base/macro.hpp"
#include "taixu/common/log/logger.hpp"
#include "vk_shader.hpp"
#include "vk_utils.hpp"


#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.hpp>

#include "backends/imgui_impl_vulkan.h"

#include <ranges>

/**
 * @brief Globale dynamic dispatch loader, only need write once
 */
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE


TX_NAMESPACE_BEGIN

/**
 * @brief Get the Device Extensions object
 *
 * @param physical_device
 * @return tx_unordered_set<tx_string>
 */
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
    static constexpr uint32_t NVIDIA_VENDOR_ID = 4318;
    static constexpr uint32_t INTEL_VENDOR_ID  = 0x8086;
    tx_ostringstream          oss;
    // NOLINTBEGIN
    if (NVIDIA_VENDOR_ID /* NVIDIA*/ == vendorID) {
        oss << ((driverVersion >> 22) & 0x3ff) << "." << ((driverVersion >> 14) & 0xff) << "."
            << ((driverVersion >> 6) & 0xff) << "." << (driverVersion & 0x3f);
    }
#if defined(TX_WINDOWS)// Windows only
    else if (INTEL_VENDOR_ID /* Intel, obviously */ == vendorID) {
        oss << (driverVersion >> 14) << "." << (driverVersion & 0x3fff);
    }
#endif// ~ Windows only
    else {
        // (Old) Vulkan convention, prior to the introduction of the
        // VK_API_VERSION_VARIANT bits at the top.
        oss << (driverVersion >> 22) << "." << ((driverVersion >> 12) & 0x3ff) << "." << (driverVersion & 0xfff);
    }
    // NOLINTEND
    return oss.str();
}

/**
 * @brief score devices, first check the vulkan version, then check the device type, and check the device memory, and
 * check the device type
 *
 * @param device
 * @param surface
 * @return float
 */
float scoreDevice(vk::raii::PhysicalDevice const& device, vk::raii::SurfaceKHR const& surface) {
    static constexpr float HIGH_SCORE = 500.0f;
    static constexpr float LOW_SCORE  = 500.0f;

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
    for (auto&& prop : queue_family_props) {
        INFO_LOG("\t{} ({} queues)", vk::to_string(prop.queueFlags), prop.queueCount);
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

    if (!findQueueFamily(device, surface, queue_family_props, vk::QueueFlagBits::eGraphics)) {
        INFO_LOG("Discarding device '{}': no graphics queue found", tx_string(props.deviceName.data()));
        return -1.0f;
    }

    if (auto const features = device.getFeatures(); !features.samplerAnisotropy) {
        INFO_LOG("Discarding device '{}': samplerAnisotropy not supported", tx_string(props.deviceName.data()));
        return -1.f;
    }

    float score = 0.0f;
    if (props.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
        score += HIGH_SCORE;
    } else if (props.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) {
        score += LOW_SCORE;
    }

    return score;
}

ResValT<vk::raii::PhysicalDevice> createPhysicsDevice(vk::raii::Instance const&   instance,
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

struct NeededQueueResult {
    uint32_t            graphics_family_index{0};
    uint32_t            present_family_index{0};
    tx_vector<uint32_t> queue_family_indices{};
};
NeededQueueResult getNeedQueueIndices(vk::raii::PhysicalDevice const& physical_device,
                                      vk::raii::SurfaceKHR const&     surface) {
    auto const queue_family_props = physical_device.getQueueFamilyProperties();

    NeededQueueResult ret;

    if (auto const index =
                findQueueFamily(physical_device, surface, queue_family_props, vk::QueueFlagBits::eGraphics)) {
        ret.graphics_family_index = *index;
        ret.queue_family_indices.emplace_back(*index);
    } else {
        auto graphics =
                findQueueFamily(physical_device, VK_NULL_HANDLE, queue_family_props, vk::QueueFlagBits::eGraphics);
        auto present = findQueueFamily(physical_device, surface, queue_family_props, std::nullopt);

        assert(graphics && present);

        ret.graphics_family_index = *graphics;
        ret.present_family_index  = *present;

        ret.queue_family_indices.emplace_back(*graphics);
        if (*graphics != *present) {
            ret.queue_family_indices.emplace_back(*present);
        }
    }

    return ret;
}

ResValT<std::tuple<vk::raii::Device, NeededQueueResult>> createDevice(vk::raii::PhysicalDevice const& physical_device,
                                                                      vk::raii::SurfaceKHR const&     surface) {
    tx_vector<const char*> enabled_dev_extensions{};
    enabled_dev_extensions.emplace_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
#if defined(TX_APPLE)
    enabled_dev_extensions.emplace_back("VK_KHR_portability_subset");
#endif
    INFO_LOG("Enabled device extensions: {}", enabled_dev_extensions);

    auto res = getNeedQueueIndices(physical_device, surface);

    if (res.queue_family_indices.empty()) {
        ERROR_LOG("No queues requested");
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }

    std::array<float, 1> queue_priorities = {1.f};

    tx_vector<vk::DeviceQueueCreateInfo> queue_infos(res.queue_family_indices.size());
    for (std::size_t i = 0; i < res.queue_family_indices.size(); ++i) {
        auto& queue_info = queue_infos[i];
        queue_info.setQueueFamilyIndex(res.queue_family_indices[i])
                .setQueueCount(1)
                .setPQueuePriorities(queue_priorities.data());
    }

    vk::PhysicalDeviceFeatures features;
    features.samplerAnisotropy = VK_TRUE;

    vk::DeviceCreateInfo create_info{};
    create_info.setQueueCreateInfoCount(1)
            .setQueueCreateInfos(queue_infos)
            .setPEnabledExtensionNames(enabled_dev_extensions)
            .setPEnabledFeatures(&features);

    auto device = physical_device.createDevice(create_info);
    if (!device.has_value()) {
        ERROR_LOG("Failed to create device: {}", vk::to_string(device.error()));
        return UNEXPECTED(RetCode::VULKAN_DEVICE_CREATE_ERROR);
    }
    VULKAN_HPP_DEFAULT_DISPATCHER.init(*device.value());
    vk::raii::Device device_raii{std::move(device.value())};

    return std::make_tuple(std::move(device_raii), std::move(res));
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

RetCode
getExtensionsAndLayers(tx_vector<const char*>& enabled_layers, tx_vector<const char*>& enabled_extensions,
                       std::optional<vk::DebugUtilsMessengerCreateInfoEXT>& debug_utils_messenger_create_info_opt,
                       bool&                                                enable_debug_utils) {
    auto supported_layers = getInstanceSupportedLayers();
    if (!supported_layers.has_value()) {
        return supported_layers.error();
    }

    auto supported_extensions = getInstanceSupportedExtensions();
    if (!supported_extensions.has_value()) {
        return supported_extensions.error();
    }

#if defined(TX_DEBUG)
    #define DEBUG_LAYER_NAME "VK_LAYER_KHRONOS_validation"

    if (supported_layers.value().contains(tx_string(DEBUG_LAYER_NAME)) &&
        supported_extensions.value().contains(tx_string(VK_EXT_DEBUG_UTILS_EXTENSION_NAME))) {

        enabled_layers.emplace_back(DEBUG_LAYER_NAME);
        enabled_extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
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
        return RetCode::VULKAN_INIT_ERROR;
    }

    for (uint32_t i = 0; i < glfwexts.count; i++) {
        if (!supported_extensions.value().contains(glfwexts.names[i])) {
            ERROR_LOG("Failed to get GLFW needed Vulkan extensions: {}", glfwexts.names[i]);
            return RetCode::VULKAN_INIT_ERROR;
        }
        enabled_extensions.emplace_back(glfwexts.names[i]);
    }

    if (enable_debug_utils) {
        vk::DebugUtilsMessengerCreateInfoEXT debug_utils_messenger_create_info{};
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
    return RetCode::SUCCESS;
}

struct SwapchainResult {
    vk::raii::SwapchainKHR swapchain{VK_NULL_HANDLE};
    vk::Format             format{};
    vk::Extent2D           extent{};
};

ResValT<std::tuple<vk::raii::Instance, vk::raii::DebugUtilsMessengerEXT>> createInstance() {
    tx_vector<const char*>                              enabled_layers{};
    tx_vector<const char*>                              enabled_extensions{};
    std::optional<vk::DebugUtilsMessengerCreateInfoEXT> debug_info{std::nullopt};
    bool                                                enable_debug_utils{false};

    if (auto ret = getExtensionsAndLayers(enabled_layers, enabled_extensions, debug_info, enable_debug_utils);
        ret != RetCode::SUCCESS) {
        return UNEXPECTED(ret);
    }

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

    auto instance_raii = vk::raii::Instance{vk::raii::Context{}, instance.value};

    vk::raii::DebugUtilsMessengerEXT debug_messenger{VK_NULL_HANDLE};
    if (enable_debug_utils) {
        auto debug_messenger_expt = instance_raii.createDebugUtilsMessengerEXT(debug_info.value());
        if (!debug_messenger_expt.has_value()) {
            ERROR_LOG("Failed to create debug utils messenger: {}", vk::to_string(debug_messenger_expt.error()));
            return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
        }
        debug_messenger = std::move(debug_messenger_expt.value());
    }

    return std::make_tuple(std::move(instance_raii), std::move(debug_messenger));
}

ResValT<vk::raii::SurfaceKHR> createSurface(vk::raii::Instance const& instance, Window const* window) {
    VkSurfaceKHR surface_strct{VK_NULL_HANDLE};
    VkInstance   instance_c_ptr = *(instance);

    if (auto const res = glfwCreateWindowSurface(
                instance_c_ptr, dynamic_cast<const GLFWWindow*>(window)->getRawWindow(), nullptr, &surface_strct);
        res != VK_SUCCESS) {
        ERROR_LOG("Failed to create window surface: {}", string_VkResult(res));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }
    return vk::raii::SurfaceKHR{instance, surface_strct};
}

void initDynamicDispatchLoader() {
    // initialize minimal set of function pointers
    VULKAN_HPP_DEFAULT_DISPATCHER.init();

    // the same initialization, now with explicitly providing a DynamicLoader
    vk::DynamicLoader dl;
    VULKAN_HPP_DEFAULT_DISPATCHER.init(dl);

    // the same initialization, now with explicitly providing the initial function pointer
    auto get_instance_proc_addr = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
    VULKAN_HPP_DEFAULT_DISPATCHER.init(get_instance_proc_addr);
}

ResValT<pro::proxy<TXGFXProxy>> VulkanContext::createContext(const TXGFXCreateInfo& window_ctx) {
    initDynamicDispatchLoader();

    const auto window = window_ctx.window;
    if (!window) {
        ERROR_LOG("Window is not support vulkan");
        return UNEXPECTED(RetCode::VULKAN_UNSUPPORTED_ERROR);
    }

    auto instance_tuple = createInstance();

    if (!instance_tuple.has_value()) {
        return UNEXPECTED(instance_tuple.error());
    }

    auto&& [instance, debug_messenger] = instance_tuple.value();

    std::shared_ptr<VulkanContext> context = std::make_shared<VulkanContext>();
    context->_instance                     = std::move(instance);
    context->_debug_messenger              = std::move(debug_messenger);

    auto surface = createSurface(context->_instance, window);
    if (!surface.has_value()) {
        return UNEXPECTED(surface.error());
    }
    context->_surface = std::move(surface.value());

    auto physical_devices = createPhysicsDevice(context->_instance, context->_surface);
    if (!physical_devices.has_value()) {
        return UNEXPECTED(physical_devices.error());
    }
    context->_physical_device = std::move(physical_devices.value());

    auto device_tuple = createDevice(context->_physical_device, context->_surface);
    if (!device_tuple.has_value()) {
        return UNEXPECTED(device_tuple.error());
    }
    auto&& [device, needed_queue]   = device_tuple.value();
    context->_graphics_family_index = needed_queue.graphics_family_index;
    context->_present_family_index  = needed_queue.present_family_index;
    context->_device                = std::move(device);

    // 获取queues
    auto gfx_quque = context->_device.getQueue(context->_graphics_family_index, 0);
    if (!gfx_quque.has_value()) {
        ERROR_LOG("Failed to get graphics queue: {}", vk::to_string(gfx_quque.error()));
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }
    context->_graphics_queue = std::move(gfx_quque.value());
    if (needed_queue.queue_family_indices.size() >= 2) {
        auto present_queue = context->_device.getQueue(context->_present_family_index, 0);
        if (!present_queue.has_value()) {
            ERROR_LOG("Failed to get present queue: {}", vk::to_string(present_queue.error()));
            return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
        }
        context->_present_queue = std::move(present_queue.value());
    } else {
        context->_use_graphics_as_present = true;
    }

    auto swapchain_res = VKSwapchain::createSwapchain(context->_physical_device, context->_surface, context->_device,
                                                      window, needed_queue.queue_family_indices);
    if (swapchain_res.has_value()) {
        context->_swapchain = std::move(swapchain_res.value());
    } else {
        ERROR_LOG("Failed to create swapchain: {}", swapchain_res.error());
        return UNEXPECTED(swapchain_res.error());
    }

    auto allocator_ret =
            VulkanAllocator::createAllocator(context->_physical_device, context->_device, context->_instance);
    if (!allocator_ret.has_value()) {
        ERROR_LOG("Failed to create allocator: {}", allocator_ret.error());
        return UNEXPECTED(allocator_ret.error());
    }
    context->_allocator = std::move(allocator_ret.value());

    context->_graphics_command_pool = createCommandPool(context->_device, context->_graphics_family_index,
                                                        vk::CommandPoolCreateFlagBits::eTransient |
                                                                vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
    if (*context->_graphics_command_pool == VK_NULL_HANDLE) {
        return UNEXPECTED(RetCode::VULKAN_INIT_ERROR);
    }

    return context;
}

namespace {
void checkImguiVKResult(VkResult error) {
    if (error == 0) {
        return;
    }
    ERROR_LOG("[vulkan imgui]Error: {}", string_VkResult(error));
}
}// namespace

void VulkanContext::imguiInit() {
    INFO_LOG("Init for imgui with Vulkan.");
}

void VulkanContext::imguiDestroy() {
    INFO_LOG("Destroy for imgui with Vulkan.");
    // ImGui_ImplVulkan_Shutdown();
}

void VulkanContext::imguiPreUpdate() {
    DEBUG_LOG("PreUpdate for imgui with Vulkan.");
}

void VulkanContext::imguiUpdate() {
    DEBUG_LOG("Update for imgui with Vulkan.");
}

std::shared_ptr<TXShaderModule> VulkanContext::createShaderModule(TXShaderModuleCreateInfo const& create_info) const {
    return VulkanShaderModule::createVulkanShaderModuleule(create_info, _device);
}

TX_NAMESPACE_END
