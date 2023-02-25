//
// Created by xmmmmmovo on 2023/2/23.
//
#include "resource/asset_manager.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("asset_manager") { 
	
	taixu::Asset_Manager manager{};
    manager.loadAsset("assets/asset.json");
    manager.writeAsset();
}