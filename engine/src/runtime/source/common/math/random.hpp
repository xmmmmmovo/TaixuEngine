//
// Created by xmmmmmovo on 2023/5/17.
//

#ifndef ENGINE_RUNTIME_CORE_MATH_RANDOM_HPP
#define ENGINE_RUNTIME_CORE_MATH_RANDOM_HPP

#include "common/designs/noncopyable.hpp"
#include <random>

namespace taixu {

template<typename RandomEngine = std::default_random_engine>
class RandomNumberGenerator final : public Noncopyable {
private:
    RandomEngine _random_engine;

public:
    template<typename... Params>
    explicit RandomNumberGenerator(Params&&... params) : _random_engine(std::forward<Params>(params)...){};
    ~RandomNumberGenerator() override = default;

    template<typename... Params>
    void seed(Params&&... params) {
        _random_engine.seed(std::forward<Params>(params)...);
    }

    template<typename T>
    T get(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(_random_engine);
    }
};


}// namespace taixu

#endif// ENGINE_RUNTIME_CORE_MATH_RANDOM_HPP
