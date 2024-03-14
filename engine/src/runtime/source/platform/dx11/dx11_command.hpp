/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once
#include "management/rhi/tx_command.hpp"

namespace taixu {

class DX11CommandBuffer : public TXCommandBuffer {};

class DX11CommandPool : public TXCommandPool {
public:
    std::unique_ptr<TXCommandBuffer> allocCommandBuffer() override;
    void submitCommandBuffer(TXCommandBuffer* commandBuffer) override;
};

}// namespace taixu