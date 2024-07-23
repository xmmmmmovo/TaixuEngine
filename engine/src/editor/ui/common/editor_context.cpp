//
// Created by xmmmmmovo on 2/28/2024.
//

#include "editor_context.hpp"

namespace taixu::editor {

EditorContext g_editor_context;

bool registerCallback(const Callbacks callback_enum, const Handler& handler) {
    if (auto [iter, success] =
                g_editor_context.callback_func_map.try_emplace(callback_enum, handler);
        !success) {
        ERROR_LOG("Callback for {} already exists.", magic_enum::enum_name(callback_enum));
        return false;
    }
    INFO_LOG("Register callback for {} successful.", magic_enum::enum_name(callback_enum));
    return true;
}

}// namespace taixu::editor
