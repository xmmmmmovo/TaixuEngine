//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_APPLICATION_CONTEXT_HPP
#define TAIXUENGINE_APPLICATION_CONTEXT_HPP

#include <memory>
#include <string>

namespace taixu::editor {

enum EditorState { EDITORMODE, PLAYMODE };

struct ApplicationContext {
public:
    EditorState      state{EditorState::EDITORMODE};
    std::string_view project_path{};
};
}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_CONTEXT_HPP
