//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62

#include "common/base/macro.hpp"

#include "platform/os/windows/windows_min.hpp"

#include <cstdint>
#include <d3d11_1.h>// 已包含Windows.h

namespace taixu {

// 默认开启图形调试器具名化
// 如果不需要该项功能，可通过全局文本替换将其值设置为0
#ifndef GRAPHICS_DEBUGGER_OBJECT_NAME
    #ifdef _DEBUG
        #define GRAPHICS_DEBUGGER_OBJECT_NAME (1)
    #else
        #define GRAPHICS_DEBUGGER_OBJECT_NAME (0)
    #endif
#endif

// 安全COM组件释放宏
#define SAFE_RELEASE(p)                                                        \
    {                                                                          \
        if ((p)) {                                                             \
            (p)->Release();                                                    \
            (p) = nullptr;                                                     \
        }                                                                      \
    }


// -----------------------------
// 下面都是dx11辅助调试宏
// -----------------------------

template<uint32_t NameLengthT>
TX_INLINE void dx11SetDebugObjectName(_In_ ID3D11DeviceChild* resource,
                                      _In_ const char (&name)[NameLengthT]) {
#if (defined(DEBUG) || defined(_DEBUG)) && (GRAPHICS_DEBUGGER_OBJECT_NAME)
    resource->SetPrivateData(WKPDID_D3DDebugObjectName, NameLengthT - 1, name);
#else
    UNREFERENCED_PARAMETER(resource);
    UNREFERENCED_PARAMETER(name);
#endif
}


}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_UTILS_06142DA55E3F46AEB5BF12658B46CC62
