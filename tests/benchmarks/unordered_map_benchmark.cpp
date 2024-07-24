//
// Created by xmmmmmovo on 2023/3/11.
//
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
template<typename T>
void addData(std::unordered_map<T, int> &map, std::vector<T> const &vec) {
    for (auto &i : vec) { map[i] = 0; }
}

TEST_CASE("Benchmark unordered_map count and find") {
    std::vector<int>         invec(1000000, 0);
    std::vector<std::string> strvec(1000000);
    struct gen_rand {
        int iter;

    public:
        gen_rand() : iter(0) {}
        std::string operator()() { return std::to_string(iter++); }
    };

    std::generate_n(strvec.begin(), 1000000, gen_rand());

    std::unordered_map<int, int>         intmap;
    std::unordered_map<std::string, int> strmap;
    addData(intmap, invec);
    addData(strmap, strvec);
    // up: debug
    // down: release
    // 4.22929e+07
    // 0.325622
    BENCHMARK("int vec count") {
        for (auto &&i : invec) { intmap.count(i); }
        return 0;
    };
    // 3.57482e+07
    // 0.325033
    BENCHMARK("int vec find") {
        for (auto &&i : invec) { intmap.find(i); }
        return 0;
    };
    // 3.38796e+08
    // 7.1874e+07
    BENCHMARK("string vec count") {
        for (auto &&i : strvec) { strmap.count(i); }
        return 0;
    };
    // 3.01766e+08
    // 7.45477e+07
    BENCHMARK("string vec find") {
        for (auto &&i : strvec) { strmap.find(i); }
        return 0;
    };
}

}

