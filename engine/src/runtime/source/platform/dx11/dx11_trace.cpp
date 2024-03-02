//
// Created by xmmmmmovo on 1/5/2024.
//

#include "dx11_trace.hpp"

#include "common/log/logger.hpp"

#include "common/utils/string_utils.hpp"

namespace taixu {

HRESULT dx11TraceW(source_loc_t loc, HRESULT hr) {
    std::array<wchar_t, 256> str_buffer_error{};

    // Windows
    // SDK 8.0起DirectX的错误信息已经集成进错误码中，可以通过FormatMessageW获取错误信息字符串
    // 不需要分配字符串内存
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   str_buffer_error.data(),
                   static_cast<DWORD>(str_buffer_error.size()), nullptr);

#ifdef _DEBUG
    ERROR_LOG_LOC(loc, "出现错误: {}({:#x})", utf8Encode(str_buffer_error.data()),
                  hr);
    DebugBreak();
#else
    FATAL_LOG_LOC(loc, "出现错误: {}({:#x})", utf8Encode(str_buffer_error.data()),
                  hr);
#endif
    return hr;
}


}// namespace taixu