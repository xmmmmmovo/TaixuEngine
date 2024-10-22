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

#include "tx_context.hpp"

#include "platform/vulkan/vk_context.hpp"

#include "common/log/custom_fmt.hpp"
#include "taixu/common/log/logger.hpp"


TX_NAMESPACE_BEGIN

std::unique_ptr<TXContext> TXContext::create(const Window* window, RenderAPI api) {
    switch (api) {
        case RenderAPI::VULKAN: {
            auto res = VKContext::createVulkanContext(window);
            if (res.has_value()) {
                ERROR_LOG("Failed to create vulkan context: {}", res.error());
            }
            return std::move(res.value());
        } break;
        case RenderAPI::WGPU: {

        } break;
    }
    return nullptr;
}

TX_NAMESPACE_END
