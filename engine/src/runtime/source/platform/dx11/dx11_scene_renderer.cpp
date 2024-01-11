//
// Created by xmmmmmovo on 1/7/2024.
//

#include "platform/dx11/dx11_scene_renderer.hpp"

#include "common/log/logger.hpp"
#include "platform/dx11/dx11_trace.hpp"
#include "platform/dx11/dx11_utils.hpp"

namespace taixu {

void DX11SceneRenderer::init(Window* window) {
    HRESULT ret = S_OK;

    // 创建D3D设备 和 D3D设备上下文
    UINT create_device_flags = 0;

#if defined(DEBUG) || defined(_DEBUG)
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    // 驱动类型数组
    std::array<D3D_DRIVER_TYPE, 3> const driver_types{
            D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE};

    // 特性等级数组
    std::array<D3D_FEATURE_LEVEL, 2> feature_levels = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
    };

    D3D_FEATURE_LEVEL feature_level;

    for (auto const& driver_type : driver_types) {
        ret = D3D11CreateDevice(nullptr, driver_type, nullptr,
                                create_device_flags, feature_levels.data(),
                                feature_levels.size(), D3D11_SDK_VERSION,
                                _device.GetAddressOf(), &feature_level,
                                _device_context.GetAddressOf());

        if (ret == E_INVALIDARG) {
            // Direct3D 11.0
            // 的API不承认D3D_FEATURE_LEVEL_11_1，所以我们需要尝试特性等级11.0以及以下的版本
            ret = D3D11CreateDevice(
                    nullptr, driver_type, nullptr, create_device_flags,
                    &feature_levels[1], feature_levels.size() - 1,
                    D3D11_SDK_VERSION, _device.GetAddressOf(), &feature_level,
                    _device_context.GetAddressOf());
        }

        if (SUCCEEDED(ret)) { break; }
    }

    // 检测是否支持特性等级11.0或11.1
    if (FAILED(ret) || (feature_level != D3D_FEATURE_LEVEL_11_0 &&
                        feature_level != D3D_FEATURE_LEVEL_11_1)) {
        FATAL_LOG("Failed to create Direct3D 11 device! Please use other "
                  "graphics API or update GPU driver. eg.vulkan)");
    }

    // 检测 MSAA支持的质量等级
    _device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
                                           &_4x_msaa_quality_support);
    assert(_4x_msaa_quality_support > 0);


    ComPtrT<IDXGIDevice>   dxgi_device  = nullptr;
    ComPtrT<IDXGIAdapter>  dxgi_adapter = nullptr;
    ComPtrT<IDXGIFactory1> dxgi_factory1 =
            nullptr;// D3D11.0(包含DXGI1.1)的接口类
    ComPtrT<IDXGIFactory2> dxgi_factory2 =
            nullptr;// D3D11.1(包含DXGI1.2)特有的接口类

    // 为了正确创建 DXGI交换链，首先我们需要获取创建 D3D设备 的
    // DXGI工厂，否则会引发报错： "IDXGIFactory::CreateSwapChain: This function
    // is being called with a device from a different IDXGIFactory."
    HR_CHECK(_device.As(&dxgi_device));
    HR_CHECK(dxgi_device->GetAdapter(dxgi_adapter.GetAddressOf()));
    HR_CHECK(dxgi_adapter->GetParent(
            __uuidof(IDXGIFactory1),
            reinterpret_cast<void**>(dxgi_factory1.GetAddressOf())));

    // 查看该对象是否包含IDXGIFactory2接口
    ret = dxgi_factory1.As(&dxgi_factory2);
    // 如果包含，则说明支持D3D11.1
    if (dxgi_factory2 != nullptr) {
        HR_CHECK(_device.As(&_device1));
        HR_CHECK(_device_context.As(&_device_context1));

        // 填充各种结构体用以描述交换链
        DXGI_SWAP_CHAIN_DESC1 sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.Width  = window->width();
        sd.Height = window->height();
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        // 是否开启4倍多重采样？
        if (_enable_4x_msaa) {
            sd.SampleDesc.Count   = 4;
            sd.SampleDesc.Quality = _4x_msaa_quality_support - 1;
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
        // 为当前窗口创建交换链
        HR_CHECK(dxgi_factory2->CreateSwapChainForHwnd(
                _device.Get(), window->getHWND(), &sd, &fd, nullptr,
                _swap_chain1.GetAddressOf()));
        HR_CHECK(_swap_chain1.As(&_swap_chain));
    } else {
        // 填充DXGI_SWAP_CHAIN_DESC用以描述交换链
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferDesc.Width                   = window->width();
        sd.BufferDesc.Height                  = window->height();
        sd.BufferDesc.RefreshRate.Numerator   = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED;
        // 是否开启4倍多重采样？
        if (_enable_4x_msaa) {
            sd.SampleDesc.Count   = 4;
            sd.SampleDesc.Quality = _4x_msaa_quality_support - 1;
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
        HR_CHECK(dxgi_factory1->CreateSwapChain(_device.Get(), &sd,
                                                _swap_chain.GetAddressOf()));
    }

    // 可以禁止alt+enter全屏
    dxgi_factory1->MakeWindowAssociation(window->getHWND(),
                                         DXGI_MWA_NO_ALT_ENTER |
                                                 DXGI_MWA_NO_WINDOW_CHANGES);

    // 设置调试对象名
    dx11SetDebugObjectName(_device_context.Get(), "ImmediateContext");
    //    dx11SetDebugObjectName(_swap_chain.Get(), "SwapChain");

    // 每当窗口被重新调整大小的时候，都需要调用这个OnResize函数。现在调用
    // 以避免代码重复
    onResize(window->width(), window->height());
    window->registerOnWindowSizeFn(
            [this](int width, int height) { this->onResize(width, height); });
}

void DX11SceneRenderer::onResize(int width, int height) {}

void DX11SceneRenderer::update(float delta_time, Scene* scene) {}

DX11SceneRenderer::~DX11SceneRenderer() {}

}// namespace taixu
