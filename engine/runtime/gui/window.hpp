//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

#include <cstdint>
#include <string>

namespace taixu::interface {

class IWindow {
protected:
    std::int32_t width{0};
    std::int32_t height{0};

    std::string_view title;

public:
    virtual void init()   = 0;
    virtual void render() = 0;

    IWindow() = default;
    IWindow(std::int32_t const &width, std::int32_t const &height,
            std::string_view const &title)
        : width(width), height(height), title(title) {}
    virtual ~IWindow() = default;
};

}// namespace taixu::interface

#endif//TAIXUENGINE_WINDOW_HPP
