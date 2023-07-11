//
// Created by xmmmmmovo on 2023/7/11.
//

#ifndef TESTS_UNIT_TESTS_LIB_LOGGER_HPP
#define TESTS_UNIT_TESTS_LIB_LOGGER_HPP

#include <iostream>

namespace test {

template<typename T>
void log_info(T const& msg) {
    std::cout << "[info] " << msg << std::endl;
}

}// namespace test

#endif// TESTS_UNIT_TESTS_LIB_LOGGER_HPP
