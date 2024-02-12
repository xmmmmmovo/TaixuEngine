//
// Created by xmmmmmovo on 1/5/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_TRACE_61772769F83E46928B4697CD072E91A2

#include "common/base/macro.hpp"
#include "common/log/logger.hpp"

#include <d3d11_1.h>

namespace taixu {

/**
 * @brief this function use to trace strack and logging in debug mode
 * @param loc filename line function
 * @param hr function name
 * @note Only use in debug mode
 * @return
 */
HRESULT dx11TraceW(source_loc_t loc, HRESULT hr);

// NOLINTBEGIN

#define HR_FAILED_GOTO(hr, ...)                                                \
    if (FAILED(hr)) {                                                          \
        ERROR_LOG(__VA_ARGS__);                                                \
        goto failed;                                                           \
    }


#if defined(_DEBUG)
    #ifndef HR_CHECK
        #define HR_CHECK(x)                                                    \
            {                                                                  \
                HRESULT const hr = (x);                                        \
                if (FAILED(hr)) {                                              \
                    dx11TraceW(source_loc_t{__FILE__, __LINE__, #x}, hr);      \
                }                                                              \
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
