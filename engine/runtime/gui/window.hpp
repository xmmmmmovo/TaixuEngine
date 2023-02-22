//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

#include "window_context.hpp"

namespace taixu {

class IWindow {
protected:
    IWindowContext context{};

protected:
    IWindow() = default;

public:
    virtual void init()    = 0;
    virtual void update()  = 0;
    virtual void destroy() = 0;
    virtual ~IWindow()     = default;

    IWindow(const IWindow &)            = delete;
    IWindow &operator=(const IWindow &) = delete;
};

}// namespace taixu::gui

#endif//TAIXUENGINE_WINDOW_HPP
