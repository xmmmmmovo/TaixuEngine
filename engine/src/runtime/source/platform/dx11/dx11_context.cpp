//
// Created by xmmmmmovo on 1/19/2024.
//

#include "dx11_context.hpp"
#include "dx11_trace.hpp"

#include <d3d11_1.h>

namespace taixu {

// 驱动类型数组
constexpr std::array DRIVER_TYPES{D3D_DRIVER_TYPE_HARDWARE,
                                  D3D_DRIVER_TYPE_WARP,
                                  D3D_DRIVER_TYPE_REFERENCE};

// 特性等级数组
constexpr std::array FEATURE_LEVELS = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
};

void DX11Context::featureLevel2Version(D3D_FEATURE_LEVEL feature_level) {

    switch (feature_level) {
        case D3D_FEATURE_LEVEL_11_0:
            _major_version = 11;
            _minor_version = 0;
            break;
        case D3D_FEATURE_LEVEL_11_1:
            _major_version = 11;
            _minor_version = 1;
            break;
        default:;
    }
}

DX11Context::~DX11Context() {
    if (_device_context != nullptr) { _device_context->ClearState(); }
}

void DX11Context::init(const Window* window) {
    HRESULT ret = S_OK;

    // 创建D3D设备 和 D3D设备上下文
    UINT create_device_flags = 0;

#if defined(_DEBUG)
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL feature_level;

    for (auto const& driver_type : DRIVER_TYPES) {
        ret = D3D11CreateDevice(nullptr, driver_type, nullptr,
                                create_device_flags, FEATURE_LEVELS.data(),
                                static_cast<UINT>(FEATURE_LEVELS.size()),
                                D3D11_SDK_VERSION, _device.GetAddressOf(),
                                &feature_level, _device_context.GetAddressOf());

        if (ret == E_INVALIDARG) {
            // Direct3D 11.0
            // 的API不承认D3D_FEATURE_LEVEL_11_1，所以我们需要尝试特性等级11.0以及以下的版本
            ret = D3D11CreateDevice(
                    nullptr, driver_type, nullptr, create_device_flags,
                    &FEATURE_LEVELS[1],
                    static_cast<UINT>(FEATURE_LEVELS.size() - 1),
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

    featureLevel2Version(feature_level);

    // 检测 MSAA支持的质量等级
    getBestSupportedMSAASettings(4, this->_msaa_best_count,
                                 this->_msaa_best_qualities);

    // 设置调试对象名
    dx11SetDebugObjectName(_device_context.Get(), "ImmediateContext");
}


void DX11Context::getBestSupportedMSAASettings(const uint32_t msaa_count,
                                               uint32_t&      count,
                                               uint32_t&      quality) const {
    uint32_t num_qualities = 0;

    for (uint32_t msaa = msaa_count; msaa > 0; msaa--) {
        if (SUCCEEDED(_device->CheckMultisampleQualityLevels(_format, msaa,
                                                             &num_qualities)) &&
            num_qualities > 0) {
            count   = msaa;
            quality = num_qualities;
            break;
            ;
        }
    }
}

bool DX11Context::isSupportDX11Ver(uint32_t const level) const {
    return level <= _minor_version;
}

}// namespace taixu