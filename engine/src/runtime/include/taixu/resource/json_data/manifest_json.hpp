/**
 * @file manifest_json.hpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2025-02-24
 *
 * Copyright (c) 2025 xmmmmmovo
 *
 */

#pragma once

#include "common/hal/tx_string.hpp"

namespace taixu {

struct Manifest {
    tx_string name{};
    tx_string version{};
    tx_string author{};
    tx_string description{};
};

}// namespace taixu
