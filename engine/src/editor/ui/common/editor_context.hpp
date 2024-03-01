//
// Created by xmmmmmovo on 2/28/2024.
//

#pragma once

#include "engine/engine.hpp"
#include "gameplay/gui/window.hpp"

namespace taixu::editor {

enum class EnumCallbacks : uint16_t {
    MENU_FILE,
    MENU_NEW_PROJECT,
    MENU_OPEN_PROJECT,
    MENU_SAVE_PROJECT,
    MENU_SAVE_PROJECT_AS,
    MENU_EXIT,
};

struct EditorContext final {
    Engine* engine_ptr{nullptr};
    std::unordered_map<EnumCallbacks, std::function<void()>>
            callback_func_map{};
};

bool invokeCallback(EnumCallbacks callback);

bool registerCallback(EnumCallbacks callback_enum, std::function<void()> callback);

extern EditorContext g_editor_context;

}// namespace taixu::editor