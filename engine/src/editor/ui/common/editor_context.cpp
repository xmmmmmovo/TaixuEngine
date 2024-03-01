//
// Created by ma_fi on 2/28/2024.
//

#include "editor_context.hpp"

#include "common/log/logger.hpp"

namespace taixu::editor {

bool invokeCallback(EnumCallbacks callback) {
    auto iter = g_editor_context.callback_func_map.find(callback);
    if (iter == g_editor_context.callback_func_map.end()) {
        ERROR_LOG("no callback for {}", magic_enum::enum_name(callback));
        return false;
    }
    iter->second();
    return true;
}

bool registerCallback(EnumCallbacks         callback_enum,
                      std::function<void()> callback) {
    auto iter = g_editor_context.callback_func_map.find(callback_enum);
    if (iter != g_editor_context.callback_func_map.end()) {
        ERROR_LOG("callback for {} already exists",
                  magic_enum::enum_name(callback_enum));
        return false;
    }
    g_editor_context.callback_func_map[callback_enum] = std::move(callback);
    return true;
}

EditorContext g_editor_context;

}// namespace taixu::editor