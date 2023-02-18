//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_MENU_COMPONENT_HPP
#define TAIXUENGINE_MENU_COMPONENT_HPP

#include "interface/component.hpp"

namespace taixu::editor {

class MenuComponent : public IComponent {
public:
    void init() override {}
    void update() override {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {
                if (ImGui::MenuItem("open")) {}
                if (ImGui::MenuItem("save as")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
