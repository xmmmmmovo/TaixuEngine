//
// Created by xmmmmmovo on 2023/4/25.
//

#include "catch2/catch_test_macros.hpp"

#include "resource/helper/image_helper.hpp"


TEST_CASE("load image tests", "[image helper tests]") {
    constexpr auto path        = "./test-assets/textures/block.png";
    constexpr auto path255_128 = "./test-assets/textures/block255_128.png";
    constexpr auto path256_128 = "./test-assets/textures/block_256_128.png";

    auto image = taixu::loadImage(path);

    REQUIRE(image->w == 128);
}

TEST_CASE("compress image tests", "[image helper tests]") {
    constexpr auto path = "/example_proj/assets/textures/concreteTexture.png";
}
