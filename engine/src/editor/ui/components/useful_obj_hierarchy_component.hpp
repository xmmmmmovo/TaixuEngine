//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP

#include <iostream>
#include <string>

#include "ui/common/ui_component.hpp"


namespace taixu::editor {


class UsefulObjectComponent : public AbstractUIComponent {
protected:
    ImGuiTreeNodeFlags const parent_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
    ImGuiTreeNodeFlags const leaf_flags   = ImGuiTreeNodeFlags_SpanAvailWidth |
                                          ImGuiTreeNodeFlags_Leaf |
                                          ImGuiTreeNodeFlags_NoTreePushOnOpen;

public:
    explicit UsefulObjectComponent(ViewModel *view_model)
        : AbstractUIComponent(view_model) {}

    void update() override {
        for (auto &obj : _view_model->useful_objs_hierarchy) {
            if (ImGui::TreeNodeEx(obj.name.c_str(), parent_flags)) {
                for (auto &child : obj.children) {
                    ImGui::TreeNodeEx(child.name.c_str(), leaf_flags);
                    if (ImGui::IsMouseDoubleClicked(0) &&
                        ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
                        spdlog::info("Double Clicked on: {}", child.name);
                    }
                }
                ImGui::TreePop();
            }
        }
    }
};
}// namespace taixu::editor

#endif//TAIXUENGINE_HIERARCHY_COMPONENT_HPP
