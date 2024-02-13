//
// Created by xmmmmmovo on 2/12/2024.
//

#pragma once

#include "dx11_context.hpp"
#include "dx11_core.hpp"
#include "management/graphics/rhi/tx_buffer.hpp"

namespace taixu {

D3D11_USAGE memoryUsage2D3D11Usage(EnumTXBufferMemoryUsage usage);

uint32_t memoryUsage2CPUAccessFlags(EnumTXBufferMemoryUsage usage);

D3D11_BIND_FLAG bufferUsage2BindFlags(EnumTXBufferUsage usage);

class DX11Buffer final : public TXBuffer {
private:
    ComPtrT<ID3D11Buffer> _buffer{nullptr};

private:
    explicit DX11Buffer(ComPtrT<ID3D11Buffer>&& buffer);

public:
    static std::shared_ptr<DX11Buffer> create(DX11Context*              context,
                                              TXBufferCreateInfo const& info);

    ID3D11Buffer* const* getBufferAddressOf();
    void                 map();
    void                 updateResource();
    void                 unmap();
};

}// namespace taixu