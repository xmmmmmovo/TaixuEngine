//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP


#include "ui/common/ui_component.hpp"

namespace taixu::editor {

class UsefulObjectComponent final : public AbstractUIComponent {
public:
    explicit UsefulObjectComponent(ViewModel& view_model)
        : AbstractUIComponent(view_model) {}

    static void update();
};

}// namespace taixu::editor

#endif// TAIXUENGINE_HIERARCHY_COMPONENT_HPP
