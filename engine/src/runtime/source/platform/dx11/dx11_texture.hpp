/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <utility>

#include "dx11_trace.hpp"
#include "management/rhi/tx_texture.hpp"

namespace taixu {

DXGI_FORMAT textureFormat2DxgiFormat(EnumTextureFormat format);

UINT textureBindFlags2D3D11BindFlags(EnumTextureBindingFlags flags);

class DX11Texture2DBase : Noncopyable {
protected:
    ComPtrT<ID3D11Texture2D>          _texture;
    ComPtrT<ID3D11ShaderResourceView> _tex_srv;
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, width, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, height, 0);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, DXGI_FORMAT, format,
                                      DXGI_FORMAT_UNKNOWN);
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, std::string, name, "");

    DX11Texture2DBase(const ComPtrT<ID3D11Texture2D>&          texture,
                      const ComPtrT<ID3D11ShaderResourceView>& tex_srv,
                      const uint32_t width, const uint32_t height,
                      const DXGI_FORMAT format, std::string name)
        : _texture(texture), _tex_srv(tex_srv), _width(width), _height(height),
          _format(format), _name(std::move(name)) {}

public:
    static std::unique_ptr<DX11Texture2DBase>
    create(std::string const& name, const CD3D11_TEXTURE2D_DESC& texDesc,
           const CD3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc);


    [[nodiscard]] ID3D11Texture2D* getTexture2D() const {
        return _texture.Get();
    }

    /**
     * @brief Get Texture 2D Shader Resource View
     * @return
     */
    [[nodiscard]] ID3D11ShaderResourceView* getTextureSRV() const {
        return _tex_srv.Get();
    }
};

class DX11Texture2D : public TXTexture2D {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, mip_levels, 1);
    ComPtrT<ID3D11RenderTargetView>    _tex_rtv;
    ComPtrT<ID3D11UnorderedAccessView> _tex_uav;

private:
    explicit DX11Texture2D(ComPtrT<ID3D11RenderTargetView> const&    tex_rtv,
                           ComPtrT<ID3D11UnorderedAccessView> const& tex_uav,
                           std::unique_ptr<DX11Texture2DBase>        texture,
                           uint32_t                                  mip_levels)
        : _mip_levels(mip_levels), _tex_rtv(tex_rtv), _tex_uav(tex_uav),
          texture(std::move(texture)) {}

public:
    std::unique_ptr<DX11Texture2DBase> const texture;

    ID3D11RenderTargetView* getRenderTarget() const { return _tex_rtv.Get(); }

    ID3D11UnorderedAccessView* getUnorderedAccess() const {
        return _tex_uav.Get();
    }

    static std::shared_ptr<DX11Texture2D>
    create(TXTexture2DCreateInfo const& create_info);
};

class DX11Texture2DMS : public DX11Texture2DBase {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, uint32_t, samples, 1);
    ComPtrT<ID3D11RenderTargetView> _tex_rtv;
};

class DX11TextureCube : public DX11Texture2DBase {};

}// namespace taixu