//
// Created by xmmmmmovo on 2023/2/21.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP
#define TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP

#include <string>

#include "gui/window_context.hpp"

namespace taixu::editor {


/**
 * @brief editor status enum
 */
enum EditorState {
    EDITORMODE, /*Editor mode*/
    PLAYMODE,   /*play mode*/
    IDLEMODE    /*idle mode, this mode will be used until project opened*/
};

class MainWindowContext : public IWindowContext {
public:
    /**
     * @brief editor state
     */
    EditorState state{EditorState::IDLEMODE};
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_CONTEXT_HPP
