/**
 * @file vk_shader.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-23
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_shader.hpp"

#include "taixu/common/log/logger.hpp"

TX_NAMESPACE_BEGIN

std::shared_ptr<VulkanShaderModule>
VulkanShaderModule::createVulkanShaderModuleule(TXShaderModuleCreateInfo const& info, vkraii::Device const& device) {
    std::shared_ptr<VulkanShaderModule> shader_module = std::make_shared<VulkanShaderModule>(info);

    vk::ShaderModuleCreateInfo create_info;
    create_info.setPCode(reinterpret_cast<const uint32_t*>(info.binaries)).setCodeSize(info.binaries_size);// NOLINT

    auto ret = device.createShaderModule(create_info);
    if (!ret.has_value()) {
        ERROR_LOG("Cannot create shader module. name: {}, error: {}", shader_module->name(),
                  vk::to_string(ret.error()));
        return nullptr;
    }

#ifdef TX_DEBUG
    vk::DebugUtilsObjectNameInfoEXT name_info;
    name_info.setObjectType(vk::ObjectType::eShaderModule)
            .setObjectHandle(reinterpret_cast<uint64_t>(static_cast<VkShaderModule>(*ret.value())))// NOLINT
            .setPObjectName("main");
    device.setDebugUtilsObjectNameEXT(name_info);
#endif

    shader_module->_shader_module = std::move(ret.value());
    return shader_module;
}

TX_NAMESPACE_END
