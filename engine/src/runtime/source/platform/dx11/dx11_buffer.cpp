//
// Created by xmmmmmovo on 2/12/2024.
//

#include "dx11_buffer.hpp"

#include "dx11_trace.hpp"

namespace taixu {

D3D11_USAGE memoryUsage2D3D11Usage(EnumTXBufferMemoryUsage const usage) {
    switch (usage) {
        case EnumTXBufferMemoryUsage::GPU_READ_WRITE:
            return D3D11_USAGE_DEFAULT;
        case EnumTXBufferMemoryUsage::GPU_READ_ONLY:
            return D3D11_USAGE_IMMUTABLE;
        case EnumTXBufferMemoryUsage::CPU_WRITE_GPU_READ:
            return D3D11_USAGE_DYNAMIC;
        case EnumTXBufferMemoryUsage::CPU_GPU_READ_WRITE:
            return D3D11_USAGE_STAGING;
    }

    return D3D11_USAGE_DEFAULT;
}

uint32_t memoryUsage2CPUAccessFlags(EnumTXBufferMemoryUsage const usage) {
    static constexpr uint32_t NO_CPU_ACCESS = 0;

    switch (usage) {
        case EnumTXBufferMemoryUsage::GPU_READ_WRITE:
            return NO_CPU_ACCESS;
        case EnumTXBufferMemoryUsage::GPU_READ_ONLY:
            return NO_CPU_ACCESS;
        case EnumTXBufferMemoryUsage::CPU_WRITE_GPU_READ:
            return D3D11_CPU_ACCESS_WRITE;
        case EnumTXBufferMemoryUsage::CPU_GPU_READ_WRITE:
            return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
    }

    return NO_CPU_ACCESS;
}

D3D11_BIND_FLAG bufferUsage2BindFlags(EnumTXBufferUsage const usage) {
    switch (usage) {
        case EnumTXBufferUsage::UNIFORM_TEXTEL:
            break;
        case EnumTXBufferUsage::VERTEX_BUFFER:
            return D3D11_BIND_VERTEX_BUFFER;
        case EnumTXBufferUsage::INDICIES_BUFFER:
            return D3D11_BIND_INDEX_BUFFER;
        case EnumTXBufferUsage::CONSTANT_BUFFER:
            return D3D11_BIND_CONSTANT_BUFFER;
    }

    return D3D11_BIND_UNORDERED_ACCESS;
}


DX11Buffer::DX11Buffer(ComPtrT<ID3D11Buffer>&& buffer, size_t stride)
    : _stride(stride), _buffer(buffer) {}

std::shared_ptr<DX11Buffer> DX11Buffer::create(DX11Context* context,
                                               TXBufferCreateInfo const& info) {

    D3D11_BUFFER_DESC buffer_desc{};
    ZeroMemory(&buffer_desc, sizeof D3D11_BUFFER_DESC);

    buffer_desc.Usage          = memoryUsage2D3D11Usage(info.memory_usage);
    buffer_desc.ByteWidth      = static_cast<UINT>(info.size);
    buffer_desc.BindFlags      = bufferUsage2BindFlags(info.usage);
    buffer_desc.CPUAccessFlags = memoryUsage2CPUAccessFlags(info.memory_usage);

    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof D3D11_SUBRESOURCE_DATA);
    data.pSysMem = info.data_ptr;

    ComPtrT<ID3D11Buffer> buffer{nullptr};
    const HRESULT hr = context->device()->CreateBuffer(&buffer_desc, &data,
                                                       buffer.GetAddressOf());
    HR_FAILED_GOTO(hr, "Create buffer failed.");

    return std::shared_ptr<DX11Buffer>(
            new DX11Buffer(std::move(buffer), info.stride));
failed:
    return nullptr;
}

ID3D11Buffer* const* DX11Buffer::getBufferAddressOf() {
    return _buffer.GetAddressOf();
}

void DX11Buffer::map() {}

void DX11Buffer::updateResource() {}

void DX11Buffer::unmap() {}

}// namespace taixu