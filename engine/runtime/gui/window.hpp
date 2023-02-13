//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

namespace taixu::gui {

class IWindow {
public:
    virtual void init()    = 0;
    virtual void render()  = 0;
    virtual void destroy() = 0;
    virtual ~IWindow()     = default;

    IWindow()                = delete;
    IWindow(const IWindow &) = delete;
};

}// namespace taixu::gui

#endif//TAIXUENGINE_WINDOW_HPP
