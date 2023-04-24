//
// Created by xmmmmmovo on 2023/4/24.
//
#include <catch2/catch_test_macros.hpp>

#include "core/base/macro.hpp"

class A {
    PROTOTYPE(int, a, 0);
};

TEST_CASE("base", "[macro tests]") {
    A a;
    REQUIRE(a.a() == 0);
}