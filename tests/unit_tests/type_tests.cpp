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

struct B {
    virtual void f() = 0;
};

struct C : B {
    void f() override {}
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

void move_ptr(std::unique_ptr<A> const &&a) {
    std::cout << a.get() << std::endl;
}

TEST_CASE("unique pointer distribution", "[C++ trait tests]") {
    std::unique_ptr<A> a    = std::make_unique<A>();
    A                  tmpa = *a;
    tmpa.a                  = 1;
    std::cout << tmpa.a << std::endl;
    move_ptr(std::move(a));
    std::cout << a.get() << std::endl;
    std::cout << tmpa.a << std::endl;
}

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
}