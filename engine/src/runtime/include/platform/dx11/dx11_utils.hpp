//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62

#include "common/base/macro.hpp"

#include <cstdint>

namespace taixu {

/**
 * 默认开启图形调试器具名化
 * 如果不需要该项功能，可通过全局文本替换将其值设置为0
 */
#ifndef GRAPHICS_DEBUGGER_OBJECT_NAME
    #ifdef _DEBUG
        #define GRAPHICS_DEBUGGER_OBJECT_NAME (1)
    #else
        #define GRAPHICS_DEBUGGER_OBJECT_NAME (0)
    #endif
#endif

// 安全COM组件释放宏
constexpr void SAFE_RELEASE(IUnknown*& ptr) {
    if (ptr) {
        ptr->Release();
        ptr = nullptr;
    }
}

// -----------------------------
// 下面都是dx11辅助调试
// -----------------------------


/**
 * @brief 为D3D设备创建出来的对象在图形调试器中设置对象名
 * @param resource D3D11设备创建出的对象
 * @param name 对象名
 * @note 该函数仅在GRAPHICS_DEBUGGER_OBJECT_NAME宏被定义时有效
 * @note 该函数仅在_DEBUG宏被定义时有效
 * @note 该函数仅在Windows平台下有效
 */
 void dx11SetDebugObjectName(ID3D11DeviceChild*      resource,
                                      const std::string_view& name);

/**
 * @brief 为DXGI对象在图形调试器中设置对象名
 * @param object DXGI对象
 * @param name 对象名
 * @note 该函数仅在GRAPHICS_DEBUGGER_OBJECT_NAME宏被定义时有效
 * @note 该函数仅在_DEBUG宏被定义时有效
 * @note 该函数仅在Windows平台下有效
 */
void dxgiSetDebugObjectName(IDXGIObject*            object,
                                      const std::string_view& name);


}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62
