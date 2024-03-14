/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "dx11_texture.hpp"

namespace taixu {

DXGI_FORMAT textureFormat2DxgiFormat(EnumTextureFormat format) {
    switch (format) {
        case EnumTextureFormat::R8G8B8A8_UNORM:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case EnumTextureFormat::R8G8B8A8_SRGB:
            return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    }
    return DXGI_FORMAT_R8G8B8A8_UNORM;
}

std::unique_ptr<DX11Texture2DBase>
DX11Texture2DBase::create(ID3D11Device* device, std::string const& name,
                          const CD3D11_TEXTURE2D_DESC&            texDesc,
                          const CD3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc) {
    ComPtrT<ID3D11Texture2D>          texture{nullptr};
    ComPtrT<ID3D11ShaderResourceView> tex_srv{nullptr};

    HRESULT hr =
            device->CreateTexture2D(&texDesc, nullptr, texture.GetAddressOf());

    HR_FAILED_GOTO(hr, "Cannot create texture2D: {}", name)

    // 用实际产生的mip等级等数据更新
    D3D11_TEXTURE2D_DESC desc;
    texture->GetDesc(&desc);

    // 完整资源SRV
    if ((desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)) {
        hr = device->CreateShaderResourceView(texture.Get(), &srvDesc,
                                              tex_srv.GetAddressOf());
        HR_FAILED_GOTO(hr, "Cannot create texture2D shader resource view:{} ",
                       name)
    }

    return std::make_unique<DX11Texture2DBase>(texture, tex_srv, desc.Width,
                                               desc.Width, desc.Format, name);

failed:
    return nullptr;
}

std::shared_ptr<DX11Texture2D>
DX11Texture2D::create(TXTexture2DCreateInfo const& create_info) {
    return nullptr;
}

}// namespace taixu