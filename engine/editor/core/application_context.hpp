//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_APPLICATION_CONTEXT_HPP
#define TAIXUENGINE_APPLICATION_CONTEXT_HPP

#include <memory>
#include <string>

namespace taixu::editor {

/**
 * @brief editor status enum
 */
enum EditorState {
    EDITORMODE, /*Editor mode*/
    PLAYMODE,   /*play mode*/
    IDLEMODE    /*idle mode, this mode will be used until project opened*/
};

/**
 * @brief application context
 */
struct ApplicationContext {
public:
    /**
     * @brief editor state
     */
    EditorState      state{EditorState::IDLEMODE};
    /**
     * @brief project state, whether the project opened
     */
    std::string_view project_path{};
};
}// namespace taixu::editor

#endif//TAIXUENGINE_APPLICATION_CONTEXT_HPP
