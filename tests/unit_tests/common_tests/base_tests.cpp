//
// Created by xmmmmmovo on 22/10/2023.
//
#include "catch2/catch_test_macros.hpp"

#include "common/base/macro.hpp"

namespace {

class A {
    PROTOTYPE_DFT(private, int, a, 0);
    PROTOTYPE_DFT(private, int, b, 0);
};

TEST_CASE("base", "[macro tests]") {
    A a;
    REQUIRE(a.a() == 0);
}

}// namespace