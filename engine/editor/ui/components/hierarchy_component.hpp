//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP

#include <iostream>
#include <string>

#include "ui/ui_component.hpp"


namespace taixu::editor {

namespace fs = std::filesystem;

struct HierarchyNode {
    std::string                name;
    bool                       is_directory;
    std::vector<HierarchyNode> childrens;
};

class HierarchyComponent : public IUIComponent {
private:
    HierarchyNode _root_node;
    HierarchyNode _current_node;

public:
    void update() override {

        const bool is_tree = true;
        if (is_tree) {

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                       ImGuiTreeNodeFlags_SpanAvailWidth;
            bool open = ImGui::TreeNodeEx("Model", flags);
            if (open) {
                ImGui::Text("obj-1");
                ImGui::Text("obj-2");
                ImGui::Text("obj-3");
                ImGui::Text("obj-4");
                ImGui::TreePop();
            }
        } else {
            ImGui::Text("No entities");
        }
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_HIERARCHY_COMPONENT_HPP
