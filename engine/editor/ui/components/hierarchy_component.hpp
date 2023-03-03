//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP

#include <iostream>
#include <string>

#include "interface/component.hpp"

namespace fs = std::filesystem;

namespace taixu::editor {
class HierarchyComponent : public IUIComponent {
public:
    void init() override {}
    void update() override {

        const bool is_tree = 1;
        if (is_tree) {
           
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                       ImGuiTreeNodeFlags_SpanAvailWidth;
            bool open = ImGui::TreeNodeEx( "Model", flags);
            if (open) {
                ImGui::Text("obj-1");
                ImGui::Text("obj-2");
                ImGui::Text("obj-3");
                ImGui::Text("obj-4");
                ImGui::TreePop();
            }
        }
        else {
            ImGui::Text("No entities");
        }

        /* if (ImGui::TreeNode("Light")) {
            for (int i = 0; i < 2; i++) 
                 ImGui::Text("text1");
            ImGui::TreePop();
        }*/
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_HIERARCHY_COMPONENT_HPP
