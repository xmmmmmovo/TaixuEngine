//
// Created by xmmmmmovo on 21/10/2023.
//
#include "catch2/catch_test_macros.hpp"

#include "common/log/custom_fmt.hpp"
#include "taixu/common/log/logger.hpp"


namespace {

using namespace taixu;

TEST_CASE("log test", "[log tests]") {
    Logger::init();

    DEBUG_LOG("Debug log!");
    INFO_LOG("Info log!");
    WARN_LOG("Warn log!");
    ERROR_LOG("Error log!");

    Logger::destroy();
}

TEST_CASE("log fmt test", "[log tests]") {
    Logger::init();

    DEBUG_LOG("Debug log with fmt: {}", 42);
    DEBUG_LOG("Debug log with fmt: {}", std::string{"hello world"});
    DEBUG_LOG("Debug log with fmt: {}", std::string_view{"hello world"});
    DEBUG_LOG("Debug log with fmt: {}", 3.1415926);
    DEBUG_LOG("Debug log with fmt: {}", "Hello World");

    std::vector<int> v{1, 2, 3, 4, 5};
    DEBUG_LOG("Debug log with fmt: {}", v);

    Logger::destroy();
}

}// namespace
