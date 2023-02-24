//
// Created by xmmmmmovo on 2023/2/23.
//

#ifndef TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
#define TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP

namespace taixu {

/**
 * @brief inherit this class in private method
 */
class noncopyable {
protected:
    noncopyable()          = default;
    virtual ~noncopyable() = default;

public:
    noncopyable(const noncopyable &)            = delete;
    noncopyable &operator=(const noncopyable &) = delete;

    noncopyable(noncopyable &&other) noexcept            = default;
    noncopyable &operator=(noncopyable &&other) noexcept = default;
};


}// namespace taixu

#endif//TAIXUENGINE_PRIVATE_NONCOPYABLE_HPP
