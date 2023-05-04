//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

#include "core/base/noncopyable.hpp"
#include "window_context.hpp"

namespace taixu {

class IWindow : private noncopyable {
public:
    virtual void init()    = 0;
    virtual void update()  = 0;
    virtual void destroy() = 0;

    virtual bool shouldClose() const = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_WINDOW_HPP
