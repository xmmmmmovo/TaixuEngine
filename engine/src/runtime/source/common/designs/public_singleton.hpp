//
// Created by xmmmmmovo on 2023/2/20.
//

#ifndef TAIXUENGINE_PUBLIC_SINGLETON_HPP
#define TAIXUENGINE_PUBLIC_SINGLETON_HPP

#include <type_traits>

namespace taixu {

/**
 * @brief public extend singleton class
 * @tparam T Type for singleton instance
 */
template<typename T>
class PublicSingleton {
protected:
    PublicSingleton()           = default;
    ~PublicSingleton() noexcept = default;

public:
    /**
     * @brief get instance, thread safe.
     * @return static instance ref.
     */
    static T& getInstance() noexcept(std::is_nothrow_constructible_v<T>) {
        static T instance;
        return instance;
    }

    PublicSingleton(const PublicSingleton&)            = delete;
    PublicSingleton& operator=(const PublicSingleton&) = delete;
};

}// namespace taixu

#endif// TAIXUENGINE_PUBLIC_SINGLETON_HPP
