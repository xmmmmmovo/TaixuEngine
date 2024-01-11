//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1

#include "management/graphics/rhi/tx_scene_renderer.hpp"

#include "platform/os/windows/windows_min.hpp"

namespace taixu {

class DX11SceneRenderer : public AbstractSceneRenderer {
private:
    template<typename T>
    using ComPtrT = Microsoft::WRL::ComPtr<T>;

private:
    ComPtrT<ID3D11Device>        _device;
    ComPtrT<ID3D11DeviceContext> _device_context;
    ComPtrT<IDXGISwapChain>      _swap_chain;

    ComPtrT<ID3D11Device1>        _device1;
    ComPtrT<ID3D11DeviceContext1> _device_context1;
    ComPtrT<IDXGISwapChain1>      _swap_chain1;

    ComPtrT<ID3D11Texture2D>        _depth_stencil_buffer;
    ComPtrT<ID3D11DepthStencilView> _depth_stencil_view;
    ComPtrT<ID3D11RenderTargetView> _render_target_view;
    D3D11_VIEWPORT                  _view_port;

    bool          _enable_4x_msaa{false};
    std::uint32_t _4x_msaa_quality_support{0};

public:
    void init(Window* window) override;
    void update(float delta_time, Scene* scene) override;

    void onResize(int width, int height) override;

    ~DX11SceneRenderer() override;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
