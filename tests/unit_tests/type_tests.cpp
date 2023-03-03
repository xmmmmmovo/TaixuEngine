//
// Created by xmmmmmovo on 2023/2/25.
//

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>
#include <vector>

struct A {
    int a{0};
};

TEST_CASE("size type", "[C++ trait tests]") {
    std::vector<int> v{0};
    auto             s = v.size();
    std::cout << "type " << typeid(s).name() << std::endl;
}

TEST_CASE("smart pointer", "[C++ trait tests]") {
    std::shared_ptr<A> a       = std::make_shared<A>();
    std::weak_ptr<A>   weakPtr = a;
    std::cout << a.get() << std::endl;
    std::cout << weakPtr.use_count() << std::endl;

    // no memory leak
    a = std::make_shared<A>();
    std::cout << a.get() << std::endl;
    std::cout << weakPtr.use_count() << std::endl;
}