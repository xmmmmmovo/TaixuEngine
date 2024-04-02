//
// Created by xmmmmmovo on 2/12/2024.
//

#pragma once

#include "dx11_context.hpp"
#include "dx11_core.hpp"
#include "management/rhi/tx_buffer.hpp"

namespace taixu {

D3D11_USAGE memoryUsage2D3D11Usage(EnumTXBufferMemoryUsage usage);

uint32_t memoryUsage2CPUAccessFlags(EnumTXBufferMemoryUsage usage);

D3D11_BIND_FLAG bufferUsage2BindFlags(EnumTXBufferUsage usage);

class DX11Buffer final : public TXBuffer {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(private, size_t, stride, 0);

private:
    ComPtrT<ID3D11Buffer>              _buffer{nullptr};
    ComPtrT<ID3D11ShaderResourceView>  _buffer_srv{nullptr};
    ComPtrT<ID3D11UnorderedAccessView> _buffer_uav{nullptr};

private:
    explicit DX11Buffer(ComPtrT<ID3D11Buffer>&& buffer, size_t stride);

public:
    static std::shared_ptr<DX11Buffer> create(TXBufferCreateInfo const& info);

    ID3D11Buffer* const* getBufferAddressOf();
    void*                mapDiscard();
    void                 unmap() const;

    template<typename T>
    void updateResource(T* data, size_t size);
};

}// namespace taixu