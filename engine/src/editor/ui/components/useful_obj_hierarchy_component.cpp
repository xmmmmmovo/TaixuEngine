/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "useful_obj_hierarchy_component.hpp"

#include <imgui/icons/IconsLucide.h>

#include <imgui.h>
#include <magic_enum.hpp>

#include <taixu/common/log/logger.hpp>

namespace taixu::editor {

static constexpr ImGuiTreeNodeFlags PARENT_FLAGS =
        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen;
static constexpr ImGuiTreeNodeFlags LEAF_FLAGS = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf |
                                                 ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;

static tx_string_view constexpr USEFUL_OBJ_COMPONENT_NAME{"Useful Objects"};

enum class UsefulObject { CUBE, SPHERE, POINTLIGHT, DIRECTIONLIGHT, ENVIROMENTLIGHT, SPOTLIGHT };

struct UsefulObjectData {
    tx_string    name;
    UsefulObject enum_object;
};

auto buildUsefulObject() {
    std::array<ChildrensHierarchyDataNode<tx_string, HierarchyDataNode<UsefulObjectData>>, 2> objects;

    objects.at(0) = {ICON_LC_BOXES "Objects",
                     {{{ICON_LC_BOX "Cube", UsefulObject::CUBE}, {ICON_LC_BOX "Sphere", UsefulObject::SPHERE}}}};
    objects.at(1) = {ICON_LC_LAMP "Lights",
                     {{{ICON_LC_LIGHTBULB "PointLight", UsefulObject::POINTLIGHT},
                       {ICON_LC_SUNSET "DirectionalLight", UsefulObject::DIRECTIONLIGHT},
                       {ICON_LC_SUN "EnviromentLight", UsefulObject::ENVIROMENTLIGHT},
                       {ICON_LC_CONE "SpotLight", UsefulObject::SPOTLIGHT}}}};

    return objects;
}

static const auto USEFUL_OBJS_HIERARCHY = buildUsefulObject();

void UsefulObjectComponent::update() {
    if (ImGui::Begin(USEFUL_OBJ_COMPONENT_NAME.data(), nullptr, ImGuiWindowFlags_None)) {
        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
        for (auto&& obj : USEFUL_OBJS_HIERARCHY) {
            if (ImGui::TreeNodeEx(obj.data.c_str(), PARENT_FLAGS)) {
                for (auto&& child : obj.childerns) {
                    ImGui::TreeNodeEx(child.data.name.c_str(), LEAF_FLAGS);
                    if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
                        INFO_LOG("Double Clicked on: {}", magic_enum::enum_name(child.data.enum_object));
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
        ImGui::End();
    }
}
}// namespace taixu::editor
