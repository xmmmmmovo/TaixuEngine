//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
#define ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT

#include <ImGuiFileDialog.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "ui/common/ui_component.hpp"
#include <GLFW/glfw3.h>
#include <common/utils/function_utils.hpp>
#include <runtime/platform/os/path.hpp>

namespace taixu::editor {

/**
 * @brief 菜单栏组件
 */
class MenuComponent : public AbstractUIComponent {
private:
    callback<std::string_view const&> _on_new_project{nullptr};
    callback<std::string_view const&> _on_open_project{nullptr};
    callback<>                        _on_save_project{nullptr};
    callback<std::string_view const&> _on_save_as_project{nullptr};

public:
    explicit MenuComponent(ViewModel* view_model)
        : AbstractUIComponent(view_model) {}

    void
    bindCallbacks(callback<std::string_view const&> const& onNewProject,
                  callback<std::string_view const&> const& onOpenProject,
                  callback<> const&                        onSaveProject,
                  callback<std::string_view const&> const& onSaveAsProject) {
        this->_on_new_project     = onNewProject;
        this->_on_open_project    = onOpenProject;
        this->_on_save_project    = onSaveProject;
        this->_on_save_as_project = onSaveAsProject;
    }

    void update() override {
        if (ImGui::MenuItem("New Project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "NewProjectDlgKey", "Choose a Directory", nullptr,
                    getRootPath().generic_string(), 1, nullptr,
                    ImGuiFileDialogFlags_Modal);
        }
        ImGui::Separator();
        if (ImGui::MenuItem("open project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "ChooseDirDlgKey", "Choose a Directory", nullptr,
                    getRootPath().generic_string(), 1, nullptr,
                    ImGuiFileDialogFlags_Modal);
        }
        if (ImGui::MenuItem("save project")) {
            if (_on_save_project) { _on_save_project(); }
        }
        if (ImGui::MenuItem("save as project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "SaveAsDirDlgKey", "Choose a Directory", nullptr,
                    getRootPath().generic_string(), 1, nullptr,
                    ImGuiFileDialogFlags_Modal);
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
            exit(0);
        }
    }

    static void
    onDialogOpen(std::string_view const&                  key,
                 callback<std::string_view const&> const& callback) {
        if (ImGuiFileDialog::Instance()->Display(key.data())) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string const file_path =
                        ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                spdlog::debug(file_path);
                if (callback) { callback(file_path); }
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }

    void processFileDialog() {
        // display
        onDialogOpen("NewProjectDlgKey", _on_new_project);
        onDialogOpen("ChooseDirDlgKey", _on_open_project);
        onDialogOpen("SaveAsDirDlgKey", _on_save_as_project);
    }
};

}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
