//
// Created by xmmmmmovo on 2/28/2024.
//

#pragma once

#include "common/dispatch/handler.hpp"
#include "common/log/logger.hpp"

#include <magic_enum.hpp>

namespace taixu::editor {

enum class Callbacks : uint16_t {
    MENU_FILE_NEW_PROJECT, // file菜单下新建项目
    FILE_OPEN_PROJECT,     // 打开项目
    MENU_FILE_SAVE_PROJECT,// file菜单下保存项目
    MENU_FILE_EXIT,        // file菜单下退出
};

struct EditorContext final {
    std::unordered_map<Callbacks, Handler> callback_func_map{};
};

extern EditorContext g_editor_context;// NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

template<class... TArgs>
bool invokeCallback(const Callbacks callback, TArgs&&... args) {
    const auto iter = g_editor_context.callback_func_map.find(callback);
    if (iter == g_editor_context.callback_func_map.end()) {
        ERROR_LOG("No callback for {}", magic_enum::enum_name(callback));
        return false;
    }
    iter->second(args...);
    INFO_LOG("Invoke callback for {} successful.", magic_enum::enum_name(callback));
    return true;
}

bool registerCallback(Callbacks callback_enum, Handler const& handler);

}// namespace taixu::editor
