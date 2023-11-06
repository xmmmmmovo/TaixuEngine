//
// Created by xmmmmmovo on 2023/4/25.
//

#include "catch2/catch_test_macros.hpp"

#include "runtime/resource/helper/image_helper.hpp"

namespace {

TEST_CASE("load image jpeg success", "[stb_image load tests]") {
    constexpr auto path = "/example_proj/assets/textures/view.jpg";
    int            width, height, channels;

    auto data = taixu::loadImage(path, &width, &height, &channels);

    REQUIRE(data != nullptr);
}


TEST_CASE("load image png success", "[stb_image load tests]") {
    constexpr auto path = "/example_proj/assets/textures/concreteTexture.png";
    int            width, height, channels;

    auto data = taixu::loadImage(path, &width, &height, &channels);

    REQUIRE(data != nullptr);
}

TEST_CASE("compress image png success", "[stb_image compress tests]") {
    constexpr auto path = "/example_proj/assets/textures/concreteTexture.png";
    int            width, height, channels;

    auto data = taixu::loadImage(path, &width, &height, &channels);

    REQUIRE(data != nullptr);
}

}// namespace
