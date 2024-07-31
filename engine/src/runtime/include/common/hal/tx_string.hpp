/**
 * @file tx_string.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tx_allocator.hpp"

namespace taixu {

template<typename Char, typename Traits = std::char_traits<Char>>
using tx_basic_string = std::basic_string<Char, Traits, txAllocatorT<Char>>;

using tx_string = tx_basic_string<char>;

using tx_wstring = tx_basic_string<wchar_t>;

using tx_u8string = tx_basic_string<char8_t>;

using tx_u16string = tx_basic_string<char16_t>;

using tx_u32string = tx_basic_string<char32_t>;

using tx_string_view = ::std::string_view;

}// namespace taixu
