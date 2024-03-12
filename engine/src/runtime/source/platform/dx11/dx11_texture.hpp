/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include "dx11_trace.hpp"
#include "management/rhi/tx_texture.hpp"

namespace taixu {

class DX11Texture2DBase : public TXTexture2D {
protected:
    ComPtrT<ID3D11Texture2D>          _texture;
    ComPtrT<ID3D11ShaderResourceView> _tex_srv;
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, width, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, height, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, DXGI_FORMAT, format,
                                      DXGI_FORMAT_UNKNOWN);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, std::string, name, "");

    DX11Texture2DBase() = default;

    bool create(ID3D11Device* device, std::string&& name,
                const CD3D11_TEXTURE2D_DESC&            texDesc,
                const CD3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc);

public:
    ID3D11Texture2D* getTexture2D() const { return _texture.Get(); }

    /**
     * @brief Get Texture 2D Shader Resource View
     * @return
     */
    ID3D11ShaderResourceView* getTextureSRV() const { return _tex_srv.Get(); }
};

class DX11Texture2D : public DX11Texture2DBase {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, mip_levels, 1);
    ComPtrT<ID3D11RenderTargetView>    _tex_rtv;
    ComPtrT<ID3D11UnorderedAccessView> _tex_uav;

public:
    ID3D11RenderTargetView* getRenderTarget() const { return _tex_rtv.Get(); }
    ID3D11UnorderedAccessView* getUnorderedAccess() const {
        return _tex_uav.Get();
    }

    static std::shared_ptr<DX11Texture2D>
    create(TXTexture2DCreateInfo const& create_info) {

        return nullptr;
    }
};


}// namespace taixu