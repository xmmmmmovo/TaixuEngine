//
// Created by xmmmmmovo on 2023/2/28.
//
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <functional>

void transferFunction(std::function<void()> func) { func(); }

void transferFunctionRef(std::function<void()> const &func) { func(); }

void transferFunctionRval(std::function<void()> &&func) { func(); }

template<typename Func>
void transferFunctionTemplate(Func func) {
    func();
}

template<typename Func>
void transferFunctionTemplateRef(Func const &func) {
    func();
}

template<typename Func>
void transferFunctionTemplateRval(Func &&func) {
    func();
}

int simpleFunction() {
    int a = 0;
    for (int i = 0; i < 10; ++i) { a += i; }
    return a;
}

TEST_CASE("Benchmark function transfer") {
    // up: debug
    // down: release
    // 82347.6
    BENCHMARK("transferFunction") {
        for (int i = 0; i < 1000; ++i) transferFunction(simpleFunction);
    };
    // 83200.9
    BENCHMARK("transferFunctionRef") {
        for (int i = 0; i < 1000; ++i) transferFunctionRef(simpleFunction);
    };
    // 84012.6
    BENCHMARK("transferFunctionRval") {
        for (int i = 0; i < 1000; ++i) transferFunctionRval(simpleFunction);
    };
    // 15256.7
    BENCHMARK("transferFunctionTemplate") {
        for (int i = 0; i < 1000; ++i) transferFunctionTemplate(simpleFunction);
    };
    // 15267.5
    BENCHMARK("transferFunctionTemplateRef") {
        for (int i = 0; i < 1000; ++i)
            transferFunctionTemplateRef(simpleFunction);
    };
    // 14089.5
    BENCHMARK("transferFunctionTemplateRval") {
        for (int i = 0; i < 1000; ++i)
            transferFunctionTemplateRval(simpleFunction);
    };
}