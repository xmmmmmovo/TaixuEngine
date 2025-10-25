/**
 * @file vk_swapchain.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-01
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "common/hal/tx_container.hpp"
#include "taixu/common/base/result.hpp"
#include "taixu/gameplay/gui/window.hpp"

#include "vk_framebuffer.hpp"
#include "vk_renderpass.hpp"

TX_NAMESPACE_BEGIN

class VKSwapchain final {
private:
    vk::raii::SwapchainKHR _swapchain{VK_NULL_HANDLE};
    vk::Extent2D           _extent;
    vk::SurfaceFormatKHR   _swapchain_format;
    vk::PresentModeKHR     _present_mode;

    tx_vector<vk::raii::Image>       _images;
    std::vector<vk::raii::ImageView> _image_views;

    std::vector<VulkanFramebuffer> _framebuffers;
    VulkanRenderPass               _present_renderpass{};

public:
    static ResValT<VKSwapchain> createSwapchain(vk::raii::PhysicalDevice const& physical_device,
                                                vk::raii::SurfaceKHR const& surface, vk::raii::Device const& device,
                                                const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                                                vk::PresentModeKHR present_mode = vk::PresentModeKHR::eFifo);

private:
    RetCode initSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::SurfaceKHR const& surface,
                          vk::raii::Device const& device, const Window* window,
                          const tx_vector<uint32_t>& queue_family_indices, vk::PresentModeKHR present_mode);

    RetCode initSwapchainImagesAndViews(vk::raii::Device const& device);
    RetCode initSwapchainFramebuffer(vk::raii::Device const& device);

    RetCode recreateSwapchain(vk::raii::PhysicalDevice const& physical_device, vk::raii::Device const& device,
                              const Window* window, const tx_vector<uint32_t>& queue_family_indices,
                              vk::PresentModeKHR present_mode);
};

TX_NAMESPACE_END
