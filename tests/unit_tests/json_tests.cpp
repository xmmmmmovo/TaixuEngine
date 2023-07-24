//
// Created by xmmmmmovo on 2023/2/26.
//
#include <catch2/catch_test_macros.hpp>

#include <common/base/path.hpp>
#include <runtime/resource/json/json_parser.hpp>
#include <runtime/resource/json/manifest_json.hpp>
#include <runtime/resource/json/serializable.hpp>

#include "lib/logger.hpp"

namespace {

TEST_CASE("load and dump json test simplest", "[json tests]") {
    test::log_info("load");
    std::filesystem::path path = DEBUG_PATH "/example_proj/manifest.json";
    auto manifest              = taixu::loadFromJsonFile<taixu::Manifest>(path);
    std::cout << dumpToJsonStr(manifest) << std::endl;
}

}// namespace
