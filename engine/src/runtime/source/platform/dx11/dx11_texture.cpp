/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "dx11_texture.hpp"

namespace taixu {

bool DX11Texture2DBase::create(
        ID3D11Device* device, std::string&& name,
        const CD3D11_TEXTURE2D_DESC&            texDesc,
        const CD3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc) {
    _name = std::forward<std::string>(name);
    _texture.Reset();
    _tex_srv.Reset();

    HRESULT hr =
            device->CreateTexture2D(&texDesc, nullptr, _texture.GetAddressOf());

    HR_FAILED_GOTO(hr, "Cannot create texture2D: {}", _name)

    // 用实际产生的mip等级等数据更新
    D3D11_TEXTURE2D_DESC desc;
    _texture->GetDesc(&desc);

    // 完整资源SRV
    if ((desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)) {
        hr = device->CreateShaderResourceView(_texture.Get(), &srvDesc,
                                              _tex_srv.GetAddressOf());
        HR_FAILED_GOTO(hr, "Cannot create texture2D shader resource view: {}",
                       _name)
    }

    return true;

failed:
    return false;
}

}// namespace taixu