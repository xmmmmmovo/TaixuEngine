//
// Created by xmmmmmovo on 1/20/2024.
//

#ifndef DX11_SWAPCHAIN_HPP_0F750F7CBBA44E3DA7757F24FF347D30
#define DX11_SWAPCHAIN_HPP_0F750F7CBBA44E3DA7757F24FF347D30


#include "common/base/macro.hpp"
#include "dx11_trace.hpp"
#include "gameplay/gui/window.hpp"

#include <d3d11_1.h>

namespace taixu {

class DX11SwapChain final {
    PROTOTYPE_ONLY_GETTER(protected, ComPtrT<IDXGISwapChain>, swap_chain);
    PROTOTYPE_DFT_VALPASS(protected, bool, vsync, true);
    PROTOTYPE_ONLY_GETTER(protected, ComPtrT<IDXGIFactory1>, dxgi_factory);
    PROTOTYPE_ONLY_GETTER(protected, ComPtrT<IDXGIAdapter>, dxgi_adapter);
    PROTOTYPE_ONLY_GETTER(protected, ComPtrT<IDXGIOutput>, dxgi_output);

protected:
    ComPtrT<ID3D11RenderTargetView> _render_target_view{};

public:
    void init(Window* window);

    void clearWindow() const;

    void presentToWindow() const;

    void resize(int32_t width, int32_t height);
};

}// namespace taixu

#endif// DX11_SWAPCHAIN_HPP_0F750F7CBBA44E3DA7757F24FF347D30
