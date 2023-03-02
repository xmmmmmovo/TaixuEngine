//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP

#include "interface/ui_component.hpp"

namespace taixu::editor {
class HierarchyComponent : public IUIComponent {
public:
    void init() override {}
    void update() override {
        ImGui::Selectable("aaaaaaa", false);
        ImGui::Selectable("aaaaaaa", false);
        ImGui::Selectable("aaaaaaa", false);
        ImGui::Selectable("aaaaaaa", false);
        ImGui::Selectable("bbbbbbb", true);
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_HIERARCHY_COMPONENT_HPP
