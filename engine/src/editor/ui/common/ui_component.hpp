//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_UI_COMPONENT_HPP
#define TAIXUENGINE_UI_COMPONENT_HPP

#include <taixu/common/designs/noncopyable.hpp>

#include "view_model.hpp"

namespace taixu::editor {

#define ICON_ENTRY(ICON, STR) ICON " " STR

/**
 * @brief UI component interface
 */
class AbstractUIComponent : Noncopyable {
protected:
    ViewModel& _view_model;

public:
    explicit AbstractUIComponent(ViewModel& view_model) : _view_model(view_model) {
    }
};

}// namespace taixu::editor

#endif// TAIXUENGINE_UI_COMPONENT_HPP
