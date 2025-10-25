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

#include "vk_allocator.hpp"
#include "vk_swapchain.hpp"


TX_NAMESPACE_BEGIN

namespace vkraii = vk::raii;

/**
 * @brief Vulkan Context, create resources or vk objects.
 *
 */
class VulkanContext final : private Noncopyable {
private:
    vkraii::Instance   _instance{VK_NULL_HANDLE};
    vkraii::SurfaceKHR _surface{VK_NULL_HANDLE};

    vkraii::Device         _device{VK_NULL_HANDLE};
    vkraii::PhysicalDevice _physical_device{VK_NULL_HANDLE};

    // We need one or two queues:
    // - best case: one GRAPHICS queue that can present
    // - otherwise: one GRAPHICS queue and any queue that can present
    std::uint32_t _graphics_family_index{0};
    vkraii::Queue _graphics_queue{VK_NULL_HANDLE};
    bool          _use_graphics_as_present{false};
    std::uint32_t _present_family_index{0};
    vkraii::Queue _present_queue{VK_NULL_HANDLE};

    vkraii::DebugUtilsMessengerEXT _debug_messenger{VK_NULL_HANDLE};

    VKSwapchain     _swapchain{};
    VulkanAllocator _allocator{};

    vk::raii::CommandPool _graphics_command_pool{VK_NULL_HANDLE};

public:
    static ResValT<pro::proxy<TXGFXProxy>> createContext(const TXGFXCreateInfo& window_ctx);

    static void                                   imguiInit();
    static void                                   imguiDestroy();
    static void                                   imguiPreUpdate();
    static void                                   imguiUpdate();
    [[nodiscard]] std::shared_ptr<TXShaderModule> createShaderModule(TXShaderModuleCreateInfo const&) const;
};

TX_GFX_CONTEXT_FACTORY_REGISTER(VulkanContext, RenderAPI::VULKAN);

TX_NAMESPACE_END
