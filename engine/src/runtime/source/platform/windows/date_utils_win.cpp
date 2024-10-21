//
// Created by ma_fi on 2024/6/2.
//

#include "common/utils/date_utils.hpp"

namespace taixu {

tx_string getDateString() {
    const auto now       = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);

    tm t{};
    localtime_s(&t, &in_time_t);

    tx_stringstream   ss;
    std::stringstream sss;
    ss << std::put_time(&t, "%Y-%m-%d %X");
    return ss.str();
}

}// namespace taixu
