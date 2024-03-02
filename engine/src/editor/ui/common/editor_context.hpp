//
// Created by xmmmmmovo on 2/28/2024.
//

#pragma once

#include "common/dispatch/handler.hpp"
#include "common/log/logger.hpp"
#include "engine/engine.hpp"
#include "gameplay/gui/window.hpp"

namespace taixu::editor {

enum class EnumCallbacks : uint16_t {
    MENU_FILE_NEW_PROJECT, // file菜单下新建项目
    MENU_FILE_OPEN_PROJECT,// file菜单下打开项目
    MENU_FILE_SAVE_PROJECT,// file菜单下保存项目
    MENU_FILE_EXIT,        // file菜单下退出
};

struct EditorContext final {
    std::unordered_map<EnumCallbacks, Handler> callback_func_map{};
};

extern EditorContext g_editor_context;

template<class... TArgs>
bool invokeCallback(const EnumCallbacks callback, TArgs&&... args) {
    const auto iter = g_editor_context.callback_func_map.find(callback);
    if (iter == g_editor_context.callback_func_map.end()) {
        ERROR_LOG("No callback for {}", magic_enum::enum_name(callback));
        return false;
    }
    iter->second(args...);
    INFO_LOG("Invoke callback for {} successful.",
             magic_enum::enum_name(callback));
    return true;
}

bool registerCallback(EnumCallbacks callback_enum, Handler const& handler);

}// namespace taixu::editor