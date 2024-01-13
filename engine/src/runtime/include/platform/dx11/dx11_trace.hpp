//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2

#include "common/base/macro.hpp"
#include "platform/windows/windows_min.hpp"

namespace taixu {

/**
 * @brief
 * @param strFile filename
 * @param dwLine fileline
 * @param hr function name
 * @param strMsg error message
 * @return
 */
HRESULT dx11TraceW(const char* strFile, std::int32_t dwLine, HRESULT hr,
                   const char* strMsg);

// NOLINTBEGIN

#if defined(_DEBUG)
    #ifndef HR_CHECK
        #define HR_CHECK(x)                                                    \
            {                                                                  \
                HRESULT const hr = (x);                                        \
                if (FAILED(hr)) { dx11TraceW(__FILE__, __LINE__, hr, #x); }    \
            }
    #endif
#else
    #ifndef HR_CHECK
        #define HR_CHECK(x) (x)
    #endif
#endif

// NOLINTEND

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2
