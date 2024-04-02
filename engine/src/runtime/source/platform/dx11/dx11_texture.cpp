/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "dx11_texture.hpp"

#include "dx11_core.hpp"

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

UINT textureBindFlags2D3D11BindFlags(EnumTextureBindingFlags flags) {
    switch (flags) {
        case EnumTextureBindingFlags::SHADER_BINDING:
            return (D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);
    }
    return 0;
}

std::unique_ptr<DX11Texture2DBase>
DX11Texture2DBase::create(std::string const&                      name,
                          const CD3D11_TEXTURE2D_DESC&            texDesc,
                          const CD3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc) {
    ComPtrT<ID3D11Texture2D>          texture{nullptr};
    ComPtrT<ID3D11ShaderResourceView> tex_srv{nullptr};

    HRESULT hr = g_dx11_context.device()->CreateTexture2D(
            &texDesc, nullptr, texture.GetAddressOf());

    HR_FAILED_GOTO(hr, "Cannot create texture2D: {}", name)

    // 用实际产生的mip等级等数据更新
    D3D11_TEXTURE2D_DESC desc;
    texture->GetDesc(&desc);

    // 完整资源SRV
    if ((desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)) {
        hr = g_dx11_context.device()->CreateShaderResourceView(
                texture.Get(), &srvDesc, tex_srv.GetAddressOf());
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
    const DXGI_FORMAT format = textureFormat2DxgiFormat(create_info.format);
    const UINT flags = textureBindFlags2D3D11BindFlags(create_info.flags);
    CD3D11_TEXTURE2D_DESC desc{
            format, create_info.width,      create_info.height,
            1,      create_info.mip_levels, flags};

    std::unique_ptr<DX11Texture2DBase> base_tex = DX11Texture2DBase::create(
            create_info.name, desc,
            CD3D11_SHADER_RESOURCE_VIEW_DESC{D3D11_SRV_DIMENSION_TEXTURE2D,
                                             format});

    if (base_tex == nullptr) { return nullptr; }

    ComPtrT<ID3D11RenderTargetView>    tex_rtv;
    ComPtrT<ID3D11UnorderedAccessView> tex_uav;
    if (flags & D3D11_BIND_RENDER_TARGET) {
        const HRESULT hr = g_dx11_context.device()->CreateRenderTargetView(
                base_tex->getTexture2D(), nullptr, tex_rtv.GetAddressOf());
        HR_FAILED_GOTO(hr, "Cannot create texture2D ID3D11RenderTargetView:{} ",
                       create_info.name)
    }

    if (flags & D3D11_BIND_UNORDERED_ACCESS) {
        CD3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc(
                D3D11_UAV_DIMENSION_TEXTURE2D, format);
        const HRESULT hr = g_dx11_context.device()->CreateUnorderedAccessView(
                base_tex->getTexture2D(), nullptr, tex_uav.GetAddressOf());
        HR_FAILED_GOTO(hr,
                       "Cannot create texture2D ID3D11UnorderedAccessView:{} ",
                       create_info.name)
    }

    return std::shared_ptr<DX11Texture2D>(new DX11Texture2D(
            tex_rtv, tex_uav, std::move(base_tex), create_info.mip_levels));

failed:
    return nullptr;
}

}// namespace taixu