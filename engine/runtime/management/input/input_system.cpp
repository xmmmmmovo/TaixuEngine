//
// Created by xmmmmmovo on 2023/3/28.
//

#include "input_system.hpp"

namespace taixu {

void InputSystem::processInput(float delta_time, WindowContext *context) {
    if (context->_state == EngineState::IDLEMODE) { return; }

    if (context->_state == EngineState::EDITORMODE) {
        editorInput(delta_time, context);
    } else if (context->_state == EngineState::GAMEMODE) {
        gameInput(delta_time, context);
    }
}

void InputSystem::editorInput(float delta_time, WindowContext *context) {
    for (auto const &callback : _editor_callbacks) {
        callback(delta_time, context);
    }
}

void InputSystem::gameInput(float delta_time, WindowContext *context) {
    for (auto const &callback : _game_callbacks) {
        callback(delta_time, context);
    }
}

}// namespace taixu