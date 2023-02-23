//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_COMPONENT_HPP
#define TAIXUENGINE_COMPONENT_HPP

#include <imgui.h>

namespace taixu::editor {

/**
 * @brief UI component interface
 */
class IUIComponent {
protected:
    /**
     * @brief hide constructor because this is interface
     */
    IUIComponent() = default;

public:
    /**
     * @brief init function, init some function after imgui inited.
     */
    virtual void init()   = 0;
    /**
     * @brief render update
     */
    virtual void update() = 0;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_COMPONENT_HPP
