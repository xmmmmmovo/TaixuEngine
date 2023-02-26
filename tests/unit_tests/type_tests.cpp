//
// Created by xmmmmmovo on 2023/2/25.
//

#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <iostream>

TEST_CASE("size type") {
    std::vector<int> v{0};
    auto s = v.size();
    std::cout << "type " << typeid(s).name() << std::endl;
}