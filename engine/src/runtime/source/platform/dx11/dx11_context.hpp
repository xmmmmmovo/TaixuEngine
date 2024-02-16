//
// Created by xmmmmmovo on 1/19/2024.
//

#ifndef DX11_CONTEXT_HPP_173F3494090748C38D78EEE1B934EC09
#define DX11_CONTEXT_HPP_173F3494090748C38D78EEE1B934EC09

#include "dx11_core.hpp"
#include "gameplay/gui/window.hpp"
#include "management/graphics/rhi/tx_context.hpp"

namespace taixu {

class DX11Context final : public TXContext {

    using DeviceT        = ComPtrT<ID3D11Device>;
    using DeviceContextT = ComPtrT<ID3D11DeviceContext>;

protected:
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, DXGI_FORMAT, format,
                                      DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);
    PROTOTYPE_ONLY_GETTER(protected, DeviceT, device);
    PROTOTYPE_ONLY_GETTER(protected, DeviceContextT, device_context);

    void featureLevel2Version(D3D_FEATURE_LEVEL feature_level);

public:
    ~DX11Context() override;

    void init(const Window* window);

    void getBestSupportedMSAASettings(uint32_t msaa_count, uint32_t& count,
                                      uint32_t& quality) const;

    [[nodiscard]] bool isSupportDX11Ver(uint32_t level) const;
};

}// namespace taixu

#endif// DX11_CONTEXT_HPP_173F3494090748C38D78EEE1B934EC09
