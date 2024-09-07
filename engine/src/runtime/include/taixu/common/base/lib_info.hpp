/**
 * @file lib_info.hpp
 * @author xmmmmmovo
 * @date 2024-07-27
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */
#pragma once

#include "common/utils/string_utils.hpp"

namespace taixu {

struct LibInfo {
    std::string_view name;
    std::string_view string_version;
    uint32_t         version;
};

static constexpr LibInfo LIB_INFO{.name           = "TaixuEngine",
                                  .string_version = "0.1.1",
                                  .version        = str2uint32Version("0.1.1")};


}// namespace taixu
