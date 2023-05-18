//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_UI_COMPONENT_HPP
#define TAIXUENGINE_UI_COMPONENT_HPP

#include <imgui.h>

#include "core/base/noncopyable.hpp"
#include "ui/view_model.hpp"

namespace taixu::editor {

/**
 * @brief UI component interface
 */
class AbstractUIComponent : private noncopyable {
protected:
    ViewModel *_view_model{nullptr};

public:
    AbstractUIComponent(ViewModel *view_model) : _view_model(view_model) {}

    /**
     * @brief render updateWindow
     */
    virtual void update() = 0;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_UI_COMPONENT_HPP
