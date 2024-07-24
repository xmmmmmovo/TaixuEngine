//
// Created by xmmmmmovo on 2023/5/17.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_INPUT_INPUT_STATE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_INPUT_INPUT_STATE_HPP

#include <array>
#include <limits>

namespace taixu {
struct InputState {
    std::array<std::int16_t, std::numeric_limits<std::int16_t>::max()> keys{};

    float mouse_x{0.0f}, mouse_y{0.0f};

    float mouse_scroll_offset_x{0.0f}, mouse_scroll_offset_y{0.0f};

    bool was_mouse_scrolling{false};

    InputState() { keys.fill(0); }
};
}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_INPUT_INPUT_STATE_HPP
