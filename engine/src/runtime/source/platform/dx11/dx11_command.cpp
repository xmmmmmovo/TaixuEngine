/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "dx11_command.hpp"

namespace taixu {

std::unique_ptr<TXCommandBuffer> DX11CommandPool::allocCommandBuffer() {
    return nullptr;
}

void DX11CommandPool::submitCommandBuffer(TXCommandBuffer* commandBuffer) {}

}// namespace taixu