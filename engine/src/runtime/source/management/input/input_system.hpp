//
// Created by xmmmmmovo on 2023/3/28.
//

#ifndef TAIXUENGINE_INPUT_SYSTEM_HPP
#define TAIXUENGINE_INPUT_SYSTEM_HPP

#include "input_state.hpp"
#include "key_code.hpp"

#include "common/base/macro.hpp"
#include "common/designs/public_singleton.hpp"
#include "gameplay/gui/window.hpp"

namespace taixu {

class Window;

class InputSystem final : public PublicSingleton<InputSystem> {
    friend class PublicSingleton<InputSystem>;

private:
    PROTOTYPE_ONLY_GETTER_CONST(private, InputState, state);

public:
    void initWindow(Window* window) {
        auto key_func = [this](int key, int action) {
            if (static_cast<EnumKeyState>(action) == EnumKeyState::PRESS) {
                _state.keys[key] = 1;
            } else if (static_cast<EnumKeyState>(action) ==
                       EnumKeyState::RELEASE) {
                _state.keys[key] = 0;
            }
        };

        window->registerOnKeyFn(
                [this, &key_func](int key, int scancode, int action, int mods) {
                    key_func(key, action);
                });

        window->registerOnMouseButtonFn(
                [this, &key_func](int button, int action, int mods) {
                    key_func(button, action);
                });

        window->registerOnCursorPosFn([this](double xpos, double ypos) {
            _state.mouse_x = static_cast<float>(xpos);
            _state.mouse_y = static_cast<float>(ypos);
        });

        window->registerOnScrollFn([this](double xoffset, double yoffset) {
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
    }

    [[nodiscard]] bool getInputState(int key) const {
        return _state.keys[key] == 1;
    }
};

}// namespace taixu

#endif// TAIXUENGINE_INPUT_SYSTEM_HPP
