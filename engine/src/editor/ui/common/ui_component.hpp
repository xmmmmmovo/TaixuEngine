//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_UI_COMPONENT_HPP
#define TAIXUENGINE_UI_COMPONENT_HPP

#include "imgui.h"

#include "common/designs/noncopyable.hpp"
#include "view_model.hpp"

namespace taixu::editor {

/**
 * @brief UI component interface
 */
class AbstractUIComponent : private Noncopyable {
protected:
    ViewModel* _view_model{nullptr};

public:
    explicit AbstractUIComponent(ViewModel* view_model)
        : _view_model(view_model) {}

    /**
     * @brief render updateWindow
     */
    virtual void update() = 0;
};

}// namespace taixu::editor

#endif// TAIXUENGINE_UI_COMPONENT_HPP