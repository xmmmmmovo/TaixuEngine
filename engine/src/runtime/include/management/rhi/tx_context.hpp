//
// Created by xmmmmmovo on 1/19/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"

#include <vulkan/vulkan_handles.hpp>

namespace taixu {

class TXContext final : Noncopyable {
    vk::Instance _instance{VK_NULL_HANDLE};
};

}// namespace taixu