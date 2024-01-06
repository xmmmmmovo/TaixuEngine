//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_13F76BFEDFDC4D34BB84A1D5BFCDF3BB
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_13F76BFEDFDC4D34BB84A1D5BFCDF3BB

namespace taixu {
class IRenderer {
public:
    virtual void init()                   = 0;
    virtual void update(float delta_time) = 0;
};
}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_13F76BFEDFDC4D34BB84A1D5BFCDF3BB
