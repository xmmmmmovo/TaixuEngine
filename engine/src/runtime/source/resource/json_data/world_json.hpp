//
// Created by xmmmmmovo on 2023/7/23.
//

#pragma once

#include <vector>

#include "common/hal/tx_string.hpp"
#include "taixu/common/base/macro.hpp"

TX_NAMESPACE_BEGIN

struct World {
    struct Level {
        tx_string level_name{};
        tx_string level_path{};
    };

    struct Global {
        tx_string render{};
    };

    tx_string          name{};
    Global             global{};
    std::vector<Level> levels{};
};

TX_NAMESPACE_END
