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
        : AbstractUIComponent(view_model,
                              {.name           = "Console",
                               .component_type = EnumImguiComponentType::WIDGET,
                               .update_func    = [this]() { this->update(); },
                               .end_call_back  = nullptr}) {}

private:
    void update() const {}
};
}// namespace taixu::editor

#endif// TAIXUENGINE_CONSOLE_COMPONENT_HPP
