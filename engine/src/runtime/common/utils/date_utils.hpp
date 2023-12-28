//
// Created by xmmmmmovo on 2023/3/2.
//

#ifndef TAIXUENGINE_DATE_UTILS_HPP
#define TAIXUENGINE_DATE_UTILS_HPP

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace taixu {

inline std::string getDateString() {
    auto              now       = std::chrono::system_clock::now();
    auto              in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

}// namespace taixu

#endif// TAIXUENGINE_DATE_UTILS_HPP
