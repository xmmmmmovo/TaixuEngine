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
protected:
    /**
     * @brief hide constructor because this is interface
     */
    IUIComponent() = default;

public:
    /**
     * @brief init function, init some function after imgui inited.
     */
    virtual void init() = 0;
    /**
     * @brief render update
     */
    virtual void update()                      = 0;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_UI_COMPONENT_HPP
