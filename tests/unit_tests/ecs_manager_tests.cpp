//
// Created by xmmmmmovo on 2023/4/29.
//
#include <catch2/catch_test_macros.hpp>

#include "gameplay/gui/window_context.hpp"
#include "management/graphics/render/render_api.hpp"

TEST_CASE("ecs tests", "[ecs manager tests]") {
    auto _context = taixu::WindowContext(
            1366, 768, "Test",
            createGraphicsAPILoader(taixu::GraphicsAPI::OPENGL), true);

    while (!_context.shouldClose()) { _context.swapBuffers(); }
}