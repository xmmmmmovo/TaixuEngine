//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_MENU_COMPONENT_HPP
#define TAIXUENGINE_MENU_COMPONENT_HPP

#include "core/application.hpp"
#include "interface/component.hpp"

namespace taixu::editor {

class MenuComponent : public IUIComponent {
public:
    void init() override {}
    void update() override {
        if (ImGui::MenuItem("open project")) {}
        if (ImGui::MenuItem("save project")) {}
        if (ImGui::MenuItem("save as project")) {}

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            Application::getInstance().destroy();
            exit(0);
        }
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
