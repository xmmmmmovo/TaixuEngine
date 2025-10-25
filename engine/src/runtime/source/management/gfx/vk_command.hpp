/**
 * @file vk_command.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-26
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class VulkanCommand {
private:
    vk::raii::CommandBuffer _command_buffer{VK_NULL_HANDLE};
};

TX_NAMESPACE_END
