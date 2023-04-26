//
// Created by xmmmmmovo on 2023/2/25.
//
#include <catch2/catch_test_macros.hpp>

#include "core/base/path.hpp"
#include "platform/opengl/ogl_vertexArray.hpp"
#include "resource/asset_manager.hpp"

TEST_CASE("noncopyable") {
    taixu::AssetManager am{};
    am.reset(DEBUG_PATH "example_proj");
}