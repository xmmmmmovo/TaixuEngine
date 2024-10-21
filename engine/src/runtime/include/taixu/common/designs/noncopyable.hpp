//
// Created by xmmmmmovo on 2023/2/23.
//

#ifndef TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
#define TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP

namespace taixu {

/**
 * @brief inherit this class in private method
 * @details This class adapt for interface and move only class.
 */
class Noncopyable {
protected:
    Noncopyable()          = default;
    virtual ~Noncopyable() = default;

public:
    Noncopyable(const Noncopyable&)            = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

/**
 * @brief Noncopyable for structure
 *
 */
struct StructDataNoncopyable {
protected:
    StructDataNoncopyable() = default;

public:
    StructDataNoncopyable(const StructDataNoncopyable&)            = delete;
    StructDataNoncopyable& operator=(const StructDataNoncopyable&) = delete;

    StructDataNoncopyable(StructDataNoncopyable&& other) noexcept            = default;
    StructDataNoncopyable& operator=(StructDataNoncopyable&& other) noexcept = default;
};

}// namespace taixu

#endif// TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
