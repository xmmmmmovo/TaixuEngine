//
// Created by xmmmmmovo on 2023/4/29.
//
#include <catch2/catch_test_macros.hpp>

#include "gameplay/gui/window_context.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/graphics/render/render_api.hpp"

TEST_CASE("ecs tests", "[ecs manager tests]") {
    auto coordinator = taixu::ECSCoordinator();
}

TEST_CASE("ecs category tests", "[ecs category tests]") {
    auto category = taixu::Category();

    category.addEntity(1);

    REQUIRE(category.hasEntity(1));

    category.removeEntity(1);

    REQUIRE(!category.hasEntity(1));

    category.addEntity(1);
    category.addEntity(2);

    REQUIRE(category.entities().size() == 2);

    category.addEntity(1);
    REQUIRE(category.entities().size() == 2);

    category.removeEntity(1);
    REQUIRE(category.entities().size() == 1);

    category.removeEntity(1);
    REQUIRE(category.entities().size() == 1);

    category.addEntity(2);
    category.addEntity(3);
    category.addEntity(4);
    category.addEntity(5);
    category.addEntity(6);
    category.addEntity(7);
    category.addEntity(8);
    REQUIRE(category.entities().size() == 7);

    category.removeEntity(2);
    REQUIRE(category.entities().size() == 6);

    category.removeEntity(3);
    REQUIRE(category.entities().size() == 5);
}
