//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"

namespace taixu {

/**
 * @brief 对CommandBuffer进行的封装
 * 其中主要封装有
 * - RenderPass
 * - descriptor(包括uniform等)
 * - pipeline
 */
class TXCommandBuffer {};

/**
 * @brief CommandBuffer封装
 */
class TXCommandPool : Noncopyable {
public:
    virtual std::unique_ptr<TXCommandBuffer> allocCommandBuffer()    = 0;
    virtual void submitCommandBuffer(TXCommandBuffer* commandBuffer) = 0;
};

}// namespace taixu