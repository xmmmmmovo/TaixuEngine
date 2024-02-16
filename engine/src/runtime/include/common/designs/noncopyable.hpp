//
// Created by xmmmmmovo on 2023/2/23.
//

#ifndef TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
#define TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP

namespace taixu {

/**
 * @brief inherit this class in private method
 * @details 这个类适用于接口定义，仅能用私有继承(private inheritance)
 * 继承自此类便会自动取消构造函数和复制构造函数，用于定义接口
 */
class Noncopyable {
protected:
             Noncopyable() = default;
    virtual ~Noncopyable() = default;

public:
                 Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&)   = delete;

                 Noncopyable(Noncopyable&& other) noexcept = delete;
    Noncopyable& operator=(Noncopyable&& other) noexcept   = default;
};

struct StructDataNoncopyable {
protected:
    StructDataNoncopyable() = default;

public:
    StructDataNoncopyable(const StructDataNoncopyable&)            = delete;
    StructDataNoncopyable& operator=(const StructDataNoncopyable&) = delete;

    StructDataNoncopyable(StructDataNoncopyable&& other) noexcept = default;
    StructDataNoncopyable&
    operator=(StructDataNoncopyable&& other) noexcept = default;
};

}// namespace taixu

#endif// TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
