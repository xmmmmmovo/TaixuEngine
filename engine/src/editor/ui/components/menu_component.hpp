//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
#define ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT

#include "imgui.h"
#include "imgui/file-dialog/ImGuiFileDialog.h"
#include "platform/os/path.hpp"
#include "ui/common/editor_context.hpp"
#include "ui/common/ui_component.hpp"

namespace taixu::editor {

/**
 * @brief 菜单栏组件
 */
class MenuComponent final : public AbstractUIComponent {
public:
    explicit MenuComponent(ViewModel* view_model)
        : AbstractUIComponent(
                  view_model,
                  {.name           = "Menu",
                   .component_type = EnumImguiComponentType::MENUBAR,
                   .update_func    = [this]() { this->update(); },
                   .end_call_back  = [this]() { this->endUpdate(); }}) {}

private:
    void update() const {
        if (ImGui::BeginMenu("File")) {
            static IGFD::FileDialogConfig const k_config{
                    .path              = getRootPath().generic_string(),
                    .countSelectionMax = 1,
                    .flags             = ImGuiFileDialogFlags_Modal};

            if (ImGui::MenuItem("New Project")) {
                ImGuiFileDialog::Instance()->OpenDialog("NewProjectDlgKey",
                                                        "Choose a Directory",
                                                        nullptr, k_config);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("open project")) {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey",
                                                        "Choose a Directory",
                                                        nullptr, k_config);
            }

            if (ImGui::MenuItem("save project")) {}

            if (ImGui::MenuItem("save as project")) {
                ImGuiFileDialog::Instance()->OpenDialog("SaveAsDirDlgKey",
                                                        "Choose a Directory",
                                                        nullptr, k_config);
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) {
                invokeCallback(EnumCallbacks::MENU_EXIT);
            }

            ImGui::EndMenu();
        }
    }

    void endUpdate() {}

    static void onDialogOpen(std::string_view const& key) {
        if (ImGuiFileDialog::Instance()->Display(key.data())) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string const file_path =
                        ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                DEBUG_LOG(file_path);
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }
};

}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
