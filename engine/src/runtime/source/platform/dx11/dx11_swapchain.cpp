//
// Created by xmmmmmovo on 1/20/2024.
//

#include "dx11_swapchain.hpp"


#include "dx11_utils.hpp"
#include "platform/dx11/dx11_trace.hpp"

namespace taixu {

void DX11SwapChain::init(DX11Context* context, Window* window) {
    this->_context = context;

    ZeroMemory(&_view_port, sizeof(D3D11_VIEWPORT));

    HRESULT hr{0};

    ComPtrT<IDXGIFactory2> dxgi_factory2 = nullptr;
    hr = _context->dxgi_factory().As(&dxgi_factory2);

    if (SUCCEEDED(hr) && dxgi_factory2 != nullptr &&
        _context->isSupportDX11Ver(1)) {

        // 填充各种结构体用以描述交换链
        DXGI_SWAP_CHAIN_DESC1 sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.Width  = window->window_info().width;
        sd.Height = window->window_info().height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        // 是否开启4倍多重采样？
        if (_context->enable_msaa()) {
            sd.SampleDesc.Count   = _context->msaa_best_count();
            sd.SampleDesc.Quality = _context->msaa_best_qualities() - 1;
        } else {
            sd.SampleDesc.Count   = 1;
            sd.SampleDesc.Quality = 0;
        }
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.SwapEffect  = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags       = 0;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd;
        fd.RefreshRate.Numerator   = 60;
        fd.RefreshRate.Denominator = 1;
        fd.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
        fd.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        fd.Windowed                = TRUE;

        IDXGISwapChain1* swap_chain1 = nullptr;
        // 为当前窗口创建交换链
        HR_CHECK(dxgi_factory2->CreateSwapChainForHwnd(
                _context->device().Get(), window->getHWND(), &sd, &fd, nullptr,
                &swap_chain1));
        _swap_chain = swap_chain1;
    }

    // 降级使用11版本的
    if (_swap_chain == nullptr) {
        // 填充DXGI_SWAP_CHAIN_DESC用以描述交换链
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));

        sd.BufferDesc.Width                   = window->window_info().width;
        sd.BufferDesc.Height                  = window->window_info().height;
        sd.BufferDesc.RefreshRate.Numerator   = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED;
        // 是否开启4倍多重采样？
        if (_context->enable_msaa()) {
            sd.SampleDesc.Count   = _context->msaa_best_count();
            sd.SampleDesc.Quality = _context->msaa_best_qualities() - 1;
        } else {
            sd.SampleDesc.Count   = 1;
            sd.SampleDesc.Quality = 0;
        }
        sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount  = 1;
        sd.OutputWindow = window->getHWND();
        sd.Windowed     = TRUE;
        sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags        = 0;
        HR_CHECK(_context->dxgi_factory()->CreateSwapChain(
                _context->device().Get(), &sd, _swap_chain.GetAddressOf()));
    }

    // 每当窗口被重新调整大小的时候，都需要调用这个OnResize函数。现在调用
    // 以避免代码重复
    resize(window->window_info().width, window->window_info().height);
    window->registerOnWindowSizeFn([this](const int width, const int height) {
        this->resize(width, height);
    });
}

void DX11SwapChain::presentToWindow() const {
    TX_ASSERT(_context->device_context());
    TX_ASSERT(_swap_chain);

    static constexpr std::array black{0.1f, 0.1f, 0.1f, 1.0f};
    static constexpr float      default_depth   = 1.0f;
    static constexpr float      default_stencil = 0.0f;

    _context->device_context()->ClearRenderTargetView(_render_target_view.Get(),
                                                      black.data());
    _context->device_context()->ClearDepthStencilView(
            _depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
            default_depth, default_stencil);

    // 绘制三角形
    HR_CHECK(_swap_chain->Present(0, 0));
}

void DX11SwapChain::resize(int32_t const width, int32_t const height) {

    _render_target_view.Reset();
    _depth_stencil_view.Reset();
    _depth_stencil_texture.Reset();


    _render_target_view.Reset();
    _depth_stencil_view.Reset();
    _depth_stencil_texture.Reset();

    ComPtrT<ID3D11Texture2D> backbuffer;
    HR_CHECK(_swap_chain->ResizeBuffers(1, width, height,
                                        DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, 0));
    HR_CHECK(_swap_chain->GetBuffer(
            0, __uuidof(ID3D11Texture2D),
            reinterpret_cast<void**>(backbuffer.GetAddressOf())));
    HR_CHECK(_context->device()->CreateRenderTargetView(
            backbuffer.Get(), nullptr, _render_target_view.GetAddressOf()));

    // 设置调试对象名
    dx11SetDebugObjectName(backbuffer.Get(), "BackBuffer[0]");

    backbuffer.Reset();

    D3D11_TEXTURE2D_DESC depth_stencil_desc;

    depth_stencil_desc.Width     = width;
    depth_stencil_desc.Height    = height;
    depth_stencil_desc.MipLevels = 1;
    depth_stencil_desc.ArraySize = 1;
    depth_stencil_desc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // 要使用 4X MSAA?
    if (_context->enable_msaa()) {
        depth_stencil_desc.SampleDesc.Count = _context->msaa_best_count();
        depth_stencil_desc.SampleDesc.Quality =
                _context->msaa_best_qualities() - 1;
    } else {
        depth_stencil_desc.SampleDesc.Count   = 1;
        depth_stencil_desc.SampleDesc.Quality = 0;
    }


    depth_stencil_desc.Usage          = D3D11_USAGE_DEFAULT;
    depth_stencil_desc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
    depth_stencil_desc.CPUAccessFlags = 0;
    depth_stencil_desc.MiscFlags      = 0;

    // 创建深度缓冲区以及深度模板视图
    HR_CHECK(_context->device()->CreateTexture2D(
            &depth_stencil_desc, nullptr,
            _depth_stencil_texture.GetAddressOf()));
    HR_CHECK(_context->device()->CreateDepthStencilView(
            _depth_stencil_texture.Get(), nullptr,
            _depth_stencil_view.GetAddressOf()));


    // 将渲染目标视图和深度/模板缓冲区结合到管线
    _context->device_context()->OMSetRenderTargets(
            1, _render_target_view.GetAddressOf(), _depth_stencil_view.Get());

    // 设置视口变换
    _view_port.TopLeftX = 0;
    _view_port.TopLeftY = 0;
    _view_port.Width    = static_cast<float>(width);
    _view_port.Height   = static_cast<float>(height);
    _view_port.MinDepth = 0.0f;
    _view_port.MaxDepth = 1.0f;

    _context->device_context()->RSSetViewports(1, &_view_port);

    // 设置调试对象名
    dx11SetDebugObjectName(_depth_stencil_texture.Get(), "DepthStencilBuffer");
    dx11SetDebugObjectName(_depth_stencil_view.Get(), "DepthStencilView");
    dx11SetDebugObjectName(_render_target_view.Get(), "BackBufferRTV[0]");

}

}// namespace taixu