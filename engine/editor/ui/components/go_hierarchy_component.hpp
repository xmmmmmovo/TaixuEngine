//
// Created by xmmmmmovo on 2023/5/19.
//

#ifndef ENGINE_EDITOR_UI_COMPONENTS_GO_HIERARCHY_COMPONENT_HPP
#define ENGINE_EDITOR_UI_COMPONENTS_GO_HIERARCHY_COMPONENT_HPP

#include "imgui.h"
#include "management/ecs/object/game_object.hpp"
#include "spdlog/spdlog.h"
#include "ui/ui_component.hpp"
#include <array>
#include <string>
#include <string_view>

namespace taixu::editor {

class GoHierarchyComponent : public AbstractUIComponent {
private:
    static constexpr std::array<std::string_view, 3>
            ENTITY_MENU_COMBO_ITEM_NAME = {"Add Empty Entity", "Delete Entity",
                                           "Rename Game Object"};

public:
    explicit GoHierarchyComponent(ViewModel *view_model)
        : AbstractUIComponent(view_model) {}

    void update() override {
        if (_view_model->engine_runtime_ptr->getScene() == nullptr) {
            ImGui::Text("No Open Scene");
            return;
        }

        auto &gos = _view_model->engine_runtime_ptr->getScene()->game_objs();

        for (auto &go : gos) {
            // TODO: 增加一层scene层级
            ImGuiTreeNodeFlags flags_select = ImGuiTreeNodeFlags_Leaf;
            if (_view_model->is_entity_selected &&
                go.entity() == _view_model->selected_entity) {
                flags_select |= ImGuiTreeNodeFlags_Selected;
            }

            auto tree_node = ImGui::TreeNodeEx(go.name().c_str(), flags_select);

            if (ImGui::IsItemClicked()) {
                _view_model->selected_entity    = go.entity();
                _view_model->is_entity_selected = true;
            }

            // right click menu
            auto const go_popup_name =
                    fmt::format("GamgObjectPopup{}", go.name());
            if (ImGui::IsItemClicked(1)) {
                spdlog::info("Right Clicked on Game Object: {}", go.name());
                ImGui::OpenPopup(go_popup_name.c_str());
            }

            bool open_modal{false};
            if (ImGui::BeginPopup(go_popup_name.c_str())) {
                const std::string go_menu_name =
                        "Game Object Menu " + go.name();
                for (int i = 0; i < 3; i++) {
                    const auto key =
                            fmt::format("{} {}", go_menu_name,
                                        ENTITY_MENU_COMBO_ITEM_NAME[i]);
                    ImGui::PushID(key.c_str());
                    if (ImGui::Selectable(
                                ENTITY_MENU_COMBO_ITEM_NAME[i].data())) {
                        spdlog::debug("Selected: {}", key);
                        if (i == 2) { open_modal = true; }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopID();
                }
                ImGui::EndPopup();
            }
            // end right click menu

            // rename modal popup
            auto rename_key =
                    fmt::format("Rename Game Object Modal {}", go.name());
            if (open_modal) { ImGui::OpenPopup(rename_key.c_str()); }
            if (ImGui::BeginPopupModal(rename_key.c_str(), nullptr,
                                       ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Rename the object in the follow edit line!\n\n");
                ImGui::Separator();

                static std::string buf(64, '\0');
                ImGui::InputText("##edit", buf.data(), 64,
                                 ImGuiInputTextFlags_CharsNoBlank);

                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    spdlog::debug("Rename Game Object to: {}", buf);
                    go.set_name(buf);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
            // end rename modal popup

            if (tree_node) { ImGui::TreePop(); }
        }
    }
};

}// namespace taixu::editor

#endif//ENGINE_EDITOR_UI_COMPONENTS_GO_HIERARCHY_COMPONENT_HPP