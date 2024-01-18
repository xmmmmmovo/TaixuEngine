//
// Created by xmmmmmovo on 1/19/2024.
//

#include "common/utils/date_utils.hpp"

#define _CRT_SECURE_NO_WARNINGS

namespace taixu {

std::string getDateString() {
    const auto        now       = std::chrono::system_clock::now();
    const auto        in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

}// namespace taixu