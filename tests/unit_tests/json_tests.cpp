//
// Created by xmmmmmovo on 2023/2/26.
//
#include <catch2/catch_test_macros.hpp>

#include "core/base/path.hpp"
#include "resource/json/json_parser.hpp"
#include "resource/json/project_json.hpp"
#include "resource/json/serializable.hpp"

namespace {


TEST_CASE("serialize json", "[json tests]") {
    std::cout << "Custom serialization: \n";
    std::cout << dumpToJson(taixu::Manifest{"1", "2", "3", "4"}) << std::endl;
}

TEST_CASE("deserialize json", "[json tests]") {}

}// namespace
