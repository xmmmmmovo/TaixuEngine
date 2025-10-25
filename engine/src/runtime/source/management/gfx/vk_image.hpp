/**
 * @file vk_image.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-24
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

class VulkanImage {
private:
    vk::raii::Image        _image;
    vk::raii::DeviceMemory _memory;
};

TX_NAMESPACE_END
