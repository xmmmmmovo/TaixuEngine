/**
 * @file vk_renderpass.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-23
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "taixu/common/base/macro.hpp"

#include "vk_framebuffer.hpp"

TX_NAMESPACE_BEGIN

class VulkanRenderPass {
private:
    vk::raii::RenderPass _render_pass{VK_NULL_HANDLE};
    VulkanFramebuffer    _framebuffer{};

public:
    [[nodiscard]] vk::raii::RenderPass const& getVulkanRenderPass() const noexcept {
        return _render_pass;
    }

    /**
     * @brief Create a Present Render Pass object, no depth buffer
     *
     * @param device
     * @return VulkanRenderPass
     */
    static VulkanRenderPass createPresentRenderPass(vk::raii::Device const& device) noexcept;
};

TX_NAMESPACE_END
