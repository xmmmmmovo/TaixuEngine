/**
 * @file tx_string.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "taixu/common/base/macro.hpp"
#include "tx_allocator.hpp"

namespace taixu {

template<typename Elem, typename Traits = std::char_traits<Elem>>
using tx_basic_string = ::std::basic_string<Elem, Traits, txAllocatorT<Elem>>;

using tx_string = tx_basic_string<char>;

using tx_wstring = tx_basic_string<wchar_t>;

using tx_u8string = tx_basic_string<char8_t>;

using tx_u16string = tx_basic_string<char16_t>;

using tx_u32string = tx_basic_string<char32_t>;

using tx_string_view = ::std::string_view;

template<typename Elem, typename Traits>
using tx_basic_stringstream = ::std::basic_stringstream<Elem, Traits, txAllocatorT<Elem>>;

using tx_stringstream = tx_basic_stringstream<char, ::std::char_traits<char>>;

template<typename Elem, typename Traits>
using tx_basic_ostringstream = ::std::basic_ostringstream<Elem, Traits, txAllocatorT<Elem>>;

using tx_ostringstream = tx_basic_ostringstream<char, ::std::char_traits<char>>;

namespace literals {
    NODISCARD TX_INLINE tx_string operator""_txs(const char* str, size_t len) {
        return tx_string{str, len};
    }

    NODISCARD TX_INLINE tx_wstring operator""_txws(const wchar_t* str, size_t len) {
        return tx_wstring{str, len};
    }

    NODISCARD constexpr tx_string_view operator"" _txsv(const char* str, size_t len) {
        return tx_string_view{str, len};
    }
}// namespace literals

}// namespace taixu
