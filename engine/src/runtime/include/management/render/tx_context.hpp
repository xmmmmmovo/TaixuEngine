//
// Created by xmmmmmovo on 1/19/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"

#include <vulkan/vulkan_raii.hpp>

namespace taixu {

class TXContext final : Noncopyable {
    vk::raii::Instance _instance{VK_NULL_HANDLE};
};

}// namespace taixu