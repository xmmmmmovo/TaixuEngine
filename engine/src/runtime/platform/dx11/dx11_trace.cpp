//
// Created by xmmmmmovo on 1/5/2024.
//

#include "dx11_trace.hpp"

#include "common/log/logger.hpp"


namespace taixu {

HRESULT dx11TraceW(const char* strFile, std::int32_t dwLine, HRESULT hr,
                   const char* strMsg) {
    wchar_t strBufferError[300];

    // Windows
    // SDK 8.0起DirectX的错误信息已经集成进错误码中，可以通过FormatMessageW获取错误信息字符串
    // 不需要分配字符串内存
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   strBufferError, 256, nullptr);

    source_loc_t tmp{strFile, dwLine, strMsg};
    ERROR_LOG_LOC(tmp, L"出现错误: {}({:#x})", strBufferError, hr);
    DebugBreak();
    return hr;
}

}// namespace taixu