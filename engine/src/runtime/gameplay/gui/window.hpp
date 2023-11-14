//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_WINDOW_HPP
#define TAIXUENGINE_WINDOW_HPP

#include <common/base/noncopyable.hpp>

#include "event_handler.hpp"
#include "runtime/management/scene/scene.hpp"

namespace taixu {

class Engine;

class Window : private Noncopyable {
protected:
    bool _is_vsync{true};
    bool minimize{false};
    bool fullscreen{false};

    InputState const* _input_state{nullptr};

    std::unique_ptr<EventHandler> _handler{nullptr};

public:
    virtual void init(std::unique_ptr<EventHandler> handler) {
        this->_handler = std::move(handler);
    };

    virtual void createWindow(std::string_view const& title, int32_t height,
                              int32_t width) = 0;

    virtual void update()  = 0;
    virtual void destroy() = 0;

    // vsync
    [[nodiscard]] bool isVsync() const { return _is_vsync; }
    virtual void       setVsync(bool vsync) = 0;

    virtual bool shouldClose() const = 0;
};

}// namespace taixu

#endif// TAIXUENGINE_WINDOW_HPP
