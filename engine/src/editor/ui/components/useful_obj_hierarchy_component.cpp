/*
 Copyright (c) xmmmmmovo@2024.
 */

#include "useful_obj_hierarchy_component.hpp"

#include "common/log/logger.hpp"

#include "imgui/icons/IconsLucide.h"

#include "imgui.h"

namespace taixu::editor {

static constexpr ImGuiTreeNodeFlags PARENT_FLAGS =
        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth |
        ImGuiTreeNodeFlags_DefaultOpen;
static constexpr ImGuiTreeNodeFlags LEAF_FLAGS =
        ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf |
        ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth;

static std::string_view constexpr USEFUL_OBJ_COMPONENT_NAME{"Useful Objects"};

auto buildUsefulObject() {
    std::array<ChildrensHierarchyNode<HierarchyNode>, 2> objects;

    objects.at(0) = {ICON_LC_BOXES "Objects",
                     {{
                              .name = ICON_LC_BOX "Cube",
                      },
                      {
                              .name = ICON_LC_BOX "Sphere",
                      }}};
    objects.at(1) = {ICON_LC_LAMP "Lights",
                     {{
                              .name = ICON_LC_LIGHTBULB "PointLight",
                      },
                      {
                              .name = ICON_LC_SUNSET "DirectionalLight",
                      },
                      {
                              .name = ICON_LC_SUN "EnviromentLight",
                      },
                      {
                              .name = ICON_LC_CONE "SpotLight",
                      }}};

    return objects;
}

static const auto USEFUL_OBJS_HIERARCHY = buildUsefulObject();

void UsefulObjectComponent::update() {
    if (ImGui::Begin(USEFUL_OBJ_COMPONENT_NAME.data(), nullptr,
                     ImGuiWindowFlags_None)) {
        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
        for (auto&& obj : USEFUL_OBJS_HIERARCHY) {
            if (ImGui::TreeNodeEx(obj.name.c_str(), PARENT_FLAGS)) {
                for (auto&& child : obj.childerns) {
                    ImGui::TreeNodeEx(child.name.c_str(), LEAF_FLAGS);
                    if (ImGui::IsMouseDoubleClicked(0) &&
                        ImGui::IsItemHovered(ImGuiHoveredFlags_None)) {
                        INFO_LOG("Double Clicked on: {}", child.name);
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