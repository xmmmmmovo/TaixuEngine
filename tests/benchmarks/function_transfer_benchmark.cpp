//
// Created by xmmmmmovo on 2023/2/28.
//
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <functional>

namespace {

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
    // 0.317953
    BENCHMARK("transferFunction") {
        for (int i = 0; i < 1000; ++i) transferFunction(simpleFunction);
        return 0;
    };
    // 83200.9
    // 0.316027
    BENCHMARK("transferFunctionRef") {
        for (int i = 0; i < 1000; ++i) transferFunctionRef(simpleFunction);
        return 0;
    };
    // 84012.6
    // 0.315648
    BENCHMARK("transferFunctionRval") {
        for (int i = 0; i < 1000; ++i) transferFunctionRval(simpleFunction);
        return 0;
    };
    // 15256.7
    // 0.36763
    BENCHMARK("transferFunctionTemplate") {
        for (int i = 0; i < 1000; ++i) transferFunctionTemplate(simpleFunction);
        return 0;
    };
    // 15267.5
    // 0.325641
    BENCHMARK("transferFunctionTemplateRef") {
        for (int i = 0; i < 1000; ++i)
            transferFunctionTemplateRef(simpleFunction);
        return 0;
    };
    // 14089.5
    // 0.316308
    BENCHMARK("transferFunctionTemplateRval") {
        for (int i = 0; i < 1000; ++i)
            transferFunctionTemplateRval(simpleFunction);
        return 0;
    };
}

}