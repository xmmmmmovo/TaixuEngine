//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_CONSOLE_COMPONENT_HPP
#define TAIXUENGINE_CONSOLE_COMPONENT_HPP

#include "ui/common/ui_component.hpp"

namespace taixu::editor {
class ConsoleComponent : public AbstractUIComponent {
public:
    explicit ConsoleComponent(ViewModel* view_model)
        : AbstractUIComponent(view_model) {}

    void update() override {}
};
}// namespace taixu::editor

#endif// TAIXUENGINE_CONSOLE_COMPONENT_HPP
