//
// Created by xmmmmmovo on 2023/2/25.
//
#include <catch2/catch_test_macros.hpp>

#include "core/base/path.hpp"
#include "resource/asset_manager.hpp"

TEST_CASE("asset manager load model success", "[asset manager tests]") {
    taixu::AssetManager am{};
    am.reset(DEBUG_PATH "/example_proj/assets");
    auto model = am.loadModel("models/nanosuit/nanosuit.obj");
    REQUIRE(model.has_value());
}