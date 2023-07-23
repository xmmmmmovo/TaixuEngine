//
// Created by xmmmmmovo on 2023/3/28.
//

#ifndef TAIXUENGINE_INPUT_SYSTEM_HPP
#define TAIXUENGINE_INPUT_SYSTEM_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>

#include <common/base/macro.hpp>
#include <common/base/public_singleton.hpp>
#include <runtime/gameplay/gui/window_context.hpp>
#include "input_state.hpp"

namespace taixu {

class InputSystem final : public PublicSingleton<InputSystem> {
    friend class PublicSingleton<InputSystem>;

private:
    PROTOTYPE_ONLY_GETTER_CONST(private, InputState, state)

public:
    void initCallbacks(WindowContext *context) {
        context->registerOnKeyFn(
                [this](int key, int scancode, int action, int mods) {
                    if (action == GLFW_PRESS) {
                        _state.keys[key] = 1;
                    } else if (action == GLFW_RELEASE) {
                        _state.keys[key] = 0;
                    }
                });

        context->registerOnMouseButtonFn(
                [this](int button, int action, int mods) {
                    if (action == GLFW_PRESS) {
                        _state.keys[button] = 1;
                    } else if (action == GLFW_RELEASE) {
                        _state.keys[button] = 0;
                    }
                });

        context->registerOnCursorPosFn([this](double xpos, double ypos) {
            _state.mouse_x          = static_cast<float>(xpos);
            _state.mouse_y          = static_cast<float>(ypos);
        });

        context->registerOnScrollFn([this](double xoffset, double yoffset) {
            if (static_cast<float>(xoffset) == _state.mouse_scroll_offset_x &&
                static_cast<float>(yoffset) == _state.mouse_scroll_offset_y) {
                _state.was_mouse_scrolling = false;
                return;
            }

            if (!_state.was_mouse_scrolling) {
                _state.was_mouse_scrolling = true;
            }
            _state.mouse_scroll_offset_x = static_cast<float>(xoffset);
            _state.mouse_scroll_offset_y = static_cast<float>(yoffset);
        });

        context->_input_state = &_state;
    }

    [[nodiscard]] bool getInputState(int key) const {
        return _state.keys[key] == 1;
    }
};

}// namespace taixu

#endif//TAIXUENGINE_INPUT_SYSTEM_HPP
