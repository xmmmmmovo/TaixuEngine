//
// Created by xmmmmmovo on 2023/2/26.
//
#include "catch2/catch_test_macros.hpp"

#include "runtime/resource/json/json_parser.hpp"
#include "runtime/resource/json/manifest_json.hpp"
#include "runtime/resource/json/serializable.hpp"

namespace {

TEST_CASE("load and dump json test simplest", "[json tests]") {
    INFO("load and dump json test simplest");
    std::filesystem::path path = "test-assets/manifest.json";
    auto manifest              = taixu::loadFromJsonFile<taixu::Manifest>(path);
    std::cout << dumpToJsonStr(manifest) << std::endl;
}

}// namespace
