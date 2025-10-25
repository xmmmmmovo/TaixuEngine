/**
 * @file vk_shader.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-22
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "management/gfx/tx_shader.hpp"
#include "taixu/common/base/macro.hpp"

namespace vkraii = vk::raii;

TX_NAMESPACE_BEGIN

class VulkanShaderModule : public TXShaderModule {
private:
    vk::raii::ShaderModule _shader_module{VK_NULL_HANDLE};

public:
    explicit VulkanShaderModule(TXShaderModuleCreateInfo const& create_info) : TXShaderModule(create_info) {
    }

    [[nodiscard]] vk::raii::ShaderModule const& getVulkanShaderModuleule() const noexcept {
        return _shader_module;
    }

    /**
     * @brief create vulkan shader module.
     *
     * @param info
     * @param device
     * @return std::shared_ptr<TXShaderModule>
     */
    static std::shared_ptr<VulkanShaderModule> createVulkanShaderModuleule(TXShaderModuleCreateInfo const& info,
                                                                           vkraii::Device const&           device);
};

TX_NAMESPACE_END
