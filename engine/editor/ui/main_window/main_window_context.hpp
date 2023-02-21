//
// Created by xmmmmmovo on 2023/2/21.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP
#define TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP

#include <string>

namespace taixu::editor {

enum EditorState { EDITORMODE, PLAYMODE, IDLEMODE };

struct MainWindowContext {
public:
    EditorState      state{EditorState::IDLEMODE};
    std::string_view project_path{};
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP
