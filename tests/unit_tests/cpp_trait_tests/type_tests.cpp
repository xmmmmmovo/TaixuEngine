//
// Created by xmmmmmovo on 2023/2/25.
//

#include "catch2/catch_test_macros.hpp"
#include "glm/glm.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace {

struct A {
    int a{0};
};

struct B {
    virtual void f() = 0;
};

struct C : B {
    void f() override {}
};

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

void move_ptr(std::unique_ptr<A> a) { std::cout << a.get() << std::endl; }

TEST_CASE("shared_ptr new", "[C++ trait tests]") {
    std::shared_ptr<A> a = std::make_shared<A>();
    auto               b = a;
    std::cout << a.get() << std::endl;
    a = std::make_shared<A>();
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
}

TEST_CASE("unique_pre move test", "[C++ trait tests]") {
    std::unique_ptr<A> a = std::make_unique<A>();
    auto               b = a.get();
    auto               c = std::move(a);
    REQUIRE(nullptr == a);
    REQUIRE(c.get() == b);
    REQUIRE(0 == c->a);

    std::unique_ptr<A> aa = std::make_unique<A>();
    aa->a                 = 1;
    A* d                  = aa.get();
    REQUIRE(d != nullptr);
    REQUIRE(d->a == 1);
    move_ptr(std::move(aa));
    std::cout << d->a << std::endl;
}

TEST_CASE("plus test", "[C++ trait tests]") {
    int a = 0;
    a++;
    REQUIRE(a == 1);
    ++a;
    REQUIRE(a == 2);
}

void foo() {}

TEST_CASE("test c++", "[C++ trait tests]") {
}

}// namespace