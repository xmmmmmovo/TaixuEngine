//
// Created by xmmmmmovo on 2023/7/9.
//

#pragma once

#include <string>

#include "common/hal/tx_string.hpp"

namespace taixu {

struct Manifest {
    tx_string name{};
    tx_string version{};
    tx_string author{};
    tx_string description{};
};

}// namespace taixu
