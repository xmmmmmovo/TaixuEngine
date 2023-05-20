//
// Created by xmmmmmovo on 2023/2/19.
//

#ifndef TAIXUENGINE_HIERARCHY_COMPONENT_HPP
#define TAIXUENGINE_HIERARCHY_COMPONENT_HPP

#include <iostream>
#include <string>

#include "ui/ui_component.hpp"


namespace taixu::editor {

class HierarchyComponent : public AbstractUIComponent {
private:
    ImGuiTreeNodeFlags const flags = ImGuiTreeNodeFlags_SpanAvailWidth;

public:
    explicit HierarchyComponent(ViewModel *view_model)
        : AbstractUIComponent(view_model) {}

    void update() override {}
};
}// namespace taixu::editor

#endif//TAIXUENGINE_HIERARCHY_COMPONENT_HPP
