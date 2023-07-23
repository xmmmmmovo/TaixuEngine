//
// Created by xmmmmmovo on 2023/4/25.
//

#include <catch2/catch_test_macros.hpp>
#include <stb_image.h>

#include <common/base/path.hpp>

namespace {

TEST_CASE("load image jpeg failed", "[stb_image tests]") {
    constexpr auto path = DEBUG_PATH "/tests/resources/sky_block_test.jpeg";
    int            width, height, channels;
    auto           ok   = stbi_info(path, &width, &height, &channels);
    auto           data = stbi_load(path, &width, &height, &channels, 0);

    REQUIRE(ok == 0);
    REQUIRE(data == nullptr);
}


TEST_CASE("load image png success", "[stb_image tests]") {
    constexpr auto path = DEBUG_PATH "/tests/resources/mars.png";
    int            width, height, channels;
    auto           ok   = stbi_info(path, &width, &height, &channels);
    auto           data = stbi_load(path, &width, &height, &channels, 0);

    REQUIRE(ok == 1);
    REQUIRE(data != nullptr);
}

}// namespace
