//
// Created by xmmmmmovo on 21/10/2023.
//
#include "catch2/catch_test_macros.hpp"

#include "common/utils/binary_utils.hpp"

TEST_CASE("bitScanForward32 test", "[binary utils tests]") {
    std::uint32_t const mask = 0x00000000;
    std::uint32_t const idx  = taixu::bitScanForward32(mask);
    REQUIRE(idx == -1);

    std::uint32_t const mask2 = 0x00000001;
    std::uint32_t const idx2  = taixu::bitScanForward32(mask2);
    REQUIRE(idx2 == 0);

    std::uint32_t const mask3 = 0x80000000;
    std::uint32_t const idx3  = taixu::bitScanForward32(mask3);
    REQUIRE(idx3 == 31);

    std::uint32_t const mask4 = 0x80000001;
    std::uint32_t const idx4  = taixu::bitScanForward32(mask4);
    REQUIRE(idx4 == 0);
}

TEST_CASE("bitScanReverse32 test", "[binary utils tests]") {
    std::uint32_t const mask = 0x00000000;
    std::uint32_t const idx  = taixu::bitScanReverse32(mask);
    REQUIRE(idx == -1);

    std::uint32_t const mask2 = 0x00000001;
    std::uint32_t const idx2  = taixu::bitScanReverse32(mask2);
    REQUIRE(idx2 == 0);

    std::uint32_t const mask3 = 0x80000000;
    std::uint32_t const idx3  = taixu::bitScanReverse32(mask3);
    REQUIRE(idx3 == 31);

    std::uint32_t const mask4 = 0x80000001;
    std::uint32_t const idx4  = taixu::bitScanReverse32(mask4);
    REQUIRE(idx4 == 31);
}

TEST_CASE("Is power of 2 test", "[binary utils tests]") {
    bool res = taixu::isPowerOfTwo(1);
    REQUIRE(res == true);

    res = taixu::isPowerOfTwo(2);
    REQUIRE(res == true);

    res = taixu::isPowerOfTwo(3);
    REQUIRE(res == false);

    res = taixu::isPowerOfTwo(4);
    REQUIRE(res == true);
}
