//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_UI_COMPONENT_HPP
#define TAIXUENGINE_UI_COMPONENT_HPP

#include <imgui.h>

#include "core/base/noncopyable.hpp"

namespace taixu::editor {

/**
 * @brief UI component interface
 */
class IUIComponent : private noncopyable {
public:
    /**
     * @brief render updateWindow
     */
    virtual void update()                      = 0;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_UI_COMPONENT_HPP