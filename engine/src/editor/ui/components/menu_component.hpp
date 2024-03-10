//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
#define ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT

#include "ui/common/ui_component.hpp"

namespace taixu::editor {

/**
 * @brief 菜单栏组件
 */
class MenuComponent final : public AbstractUIComponent {

public:
    explicit MenuComponent(ViewModel& view_model);

private:
    static void buildFileMenu();
    static void buildEditMenu();
    static void buildWindowMenu();
    static void buildHelpMenu();

    void endUpdate() const;

public:
    void update() const;
};

}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
