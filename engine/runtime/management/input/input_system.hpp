//
// Created by xmmmmmovo on 2023/3/28.
//

#ifndef TAIXUENGINE_INPUT_SYSTEM_HPP
#define TAIXUENGINE_INPUT_SYSTEM_HPP

#include <memory>

#include "core/base/public_singleton.hpp"
#include "gameplay/gui/window_context.hpp"

namespace taixu {

class InputSystem : public PublicSingleton<InputSystem> {
    friend class PublicSingleton<InputSystem>;

    using inputCallback = std::function<void(float, WindowContext *)>;

private:
    std::vector<inputCallback> _editor_callbacks;
    std::vector<inputCallback> _game_callbacks;

public:
    void processInput(float delta_time, WindowContext *context);

    inline void registerEditorCallback(inputCallback const &callback) {
        _editor_callbacks.push_back(callback);
    }

    inline void registerGameCallback(inputCallback const &callback) {
        _game_callbacks.push_back(callback);
    }

private:
    inline void editorInput(float delta_time, WindowContext *context);
    inline void gameInput(float delta_time, WindowContext *context);
};

}// namespace taixu

#endif//TAIXUENGINE_INPUT_SYSTEM_HPP
