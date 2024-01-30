//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"
#include "tx_command_buffer.hpp"

namespace taixu {

/**
 * @brief CommandBuffer封装
 */
class TXCommandPool : Noncopyable {
public:
    virtual TXCommandBuffer allocCommandBuffer()                     = 0;
    virtual void submitCommandBuffer(TXCommandBuffer& commandBuffer) = 0;
};

}// namespace taixu