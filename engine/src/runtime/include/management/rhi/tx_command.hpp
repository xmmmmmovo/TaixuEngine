//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"
#include "tx_buffer.hpp"
#include "tx_pipeline.hpp"
#include "tx_renderpass.hpp"

namespace taixu {

/**
 * @brief 对CommandBuffer进行的封装
 * 其中主要封装有
 * - RenderPass
 * - descriptor(包括uniform等)
 * - pipeline
 */
class TXCommandBuffer : Noncopyable {
public:
    virtual bool begin() = 0;
    virtual bool end()   = 0;

    // virtual bool beginRenderPass(TXRenderPass*  renderPass,
    // TXFrameBuffer* frameBuffer) = 0;
    virtual bool endRenderPass() = 0;

    virtual bool bindPipeline(TXPipeline* pipeline) = 0;
    // virtual bool bindDescriptor(TXDescriptor* descriptor) = 0;
    virtual bool bindVertexBuffer(TXBuffer* buffer) = 0;
    virtual bool bindIndexBuffer(TXBuffer* buffer)  = 0;
    virtual bool bindUniformBuffer(TXBuffer* buffer, uint32_t offset,
                                   uint32_t size)   = 0;

    virtual bool draw(uint32_t vertexCount, uint32_t instanceCount,
                      uint32_t firstVertex, uint32_t firstInstance) = 0;
    virtual bool drawIndexed(uint32_t indexCount, uint32_t instanceCount,
                             uint32_t firstIndex, int32_t vertexOffset,
                             uint32_t firstInstance)                = 0;
    virtual bool dispatch(uint32_t groupCountX, uint32_t groupCountY,
                          uint32_t groupCountZ)                     = 0;
};

/**
 * @brief Command Queue封装
 * @details Queue分成几类Background：背景物体，最先渲染
 * Geometry：几何体，中间渲染
 * AlphaTest：需要测试透明度的物体
 * Transparent：透明物体
 * Overdlay：后处理叠加
 */

/**
 * @brief CommandBuffer封装
 */
class TXCommandPool : Noncopyable {
public:
    virtual std::unique_ptr<TXCommandBuffer> allocCommandBuffer()    = 0;
    virtual void submitCommandBuffer(TXCommandBuffer* commandBuffer) = 0;
};

}// namespace taixu