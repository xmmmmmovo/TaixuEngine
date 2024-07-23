//
// Created by xmmmmmovo on 2023/5/16.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_INPUT_KEY_CODE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_INPUT_KEY_CODE_HPP

#include <cstdint>
namespace taixu {

enum class KeyCode : std::int8_t {
    UNKNOWN = -1,
};

enum class KeyState : std::uint8_t {
    PRESS   = 0,
    RELEASE = 1,
};

struct KeyEvent {
    KeyCode  code;
    KeyState state;
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_INPUT_KEY_CODE_HPP
