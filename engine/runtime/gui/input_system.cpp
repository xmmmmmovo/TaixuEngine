//
// Created by xmmmmmovo on 2023/3/28.
//

#include "input_system.hpp"

namespace taixu {

void InputSystem::setContext(const std::shared_ptr<WindowContext>& context) {
    this->_context = context;
}

void InputSystem::processInput(float delta_time) {
    if (_context->_state == EngineState::IDLEMODE) { return; }

    if (_context->_state == EngineState::EDITORMODE) {
        editorInput(delta_time);
    } else if (_context->_state == EngineState::GAMEMODE) {
        gameInput(delta_time);
    }
}

void InputSystem::editorInput(float delta_time) {
    for (auto const& callback : _editor_callbacks) { callback(delta_time); }
}

void InputSystem::gameInput(float delta_time) {
    for (auto const& callback : _game_callbacks) { callback(delta_time); }
}

}// namespace taixu