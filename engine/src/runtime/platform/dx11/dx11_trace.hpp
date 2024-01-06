//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2

#include "common/base/macro.hpp"
#include "platform/os/windows/windows_headers.hpp"

namespace taixu {

/**
 * @brief
 * @param strFile filename
 * @param dwLine fileline
 * @param hr function name
 * @param strMsg error message
 * @return
 */
HRESULT WINAPI dx11TraceW(_In_z_ const char* strFile, _In_ std::int32_t dwLine,
                          _In_ HRESULT hr, _In_opt_ const char* strMsg);

#if defined(_DEBUG)
    #ifndef HR
        #define HR(x)                                                          \
            {                                                                  \
                HRESULT hr = (x);                                              \
                if (FAILED(hr)) { dx11TraceW(__FILEW__, __LINE__, hr, L#x); }  \
            }
    #endif
#else
    #ifndef HR
        #define HR(x) (x)
    #endif
#endif

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2
