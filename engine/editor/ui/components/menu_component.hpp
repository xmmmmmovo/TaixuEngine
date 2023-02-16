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
        ImGui::Begin("Menu");

        ImGui::End();
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
