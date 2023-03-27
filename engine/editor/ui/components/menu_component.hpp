//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
#define ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT

#include <ImGuiFileDialog.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "application.hpp"
#include "core/base/path.hpp"
#include "core/utils/function_utils.hpp"
#include "platform/os/path.hpp"
#include "ui/ui_component.hpp"

namespace taixu::editor {

/**
 * @brief 菜单栏组件
 */
class MenuComponent : public IUIComponent {
private:
    callback<std::string_view const&> onNewProject{nullptr};
    callback<std::string_view const&> onOpenProject{nullptr};
    callback<>                        onSaveProject{nullptr};
    callback<std::string_view const&> onSaveAsProject{nullptr};

public:
    void bindCallbacks(
            callback<std::string_view const&> const& onNewProject,
            callback<std::string_view const&> const& onOpenProject,
            callback<> const&                        onSaveProject,
            callback<std::string_view const&> const& onSaveAsProject) {
        this->onNewProject    = onNewProject;
        this->onOpenProject   = onOpenProject;
        this->onSaveProject   = onSaveProject;
        this->onSaveAsProject = onSaveAsProject;
    }

    void update() override {
        if (ImGui::MenuItem("New Project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "NewProjectDlgKey", "Choose a Directory", nullptr,
#ifndef NDEBUG
                    DEBUG_PATH "/example_proj"
#else
                    getRootPath().c_str()
#endif
                    ,
                    1, nullptr, ImGuiFileDialogFlags_Modal);
        }
        ImGui::Separator();
        if (ImGui::MenuItem("open project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "ChooseDirDlgKey", "Choose a Directory", nullptr,
#ifndef NDEBUG
                    DEBUG_PATH "/example_proj"
#else
                    getRootPath().c_str()
#endif
                    ,
                    1, nullptr, ImGuiFileDialogFlags_Modal);
        }
        if (ImGui::MenuItem("save project")) {
            if (onSaveProject) { onSaveProject(); }
        }
        if (ImGui::MenuItem("save as project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "SaveAsDirDlgKey", "Choose a Directory", nullptr,
#ifndef NDEBUG
                    DEBUG_PATH "/example_proj"
#else
                    getRootPath().c_str()
#endif /* ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT */
                    ,
                    1, nullptr, ImGuiFileDialogFlags_Modal);
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            Application::getInstance().destroy();
            exit(0);
        }
    }

    static void onDialogOpen(std::string_view const&                  key,
                      callback<std::string_view const&> const& cb) {
        if (ImGuiFileDialog::Instance()->Display(key.data())) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath =
                        ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                spdlog::debug(filePath);
                if (cb) { cb(filePath); }
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }

    void processFileDialog() {
        // display
        onDialogOpen("NewProjectDlgKey", onNewProject);
        onDialogOpen("ChooseDirDlgKey", onOpenProject);
        onDialogOpen("SaveAsDirDlgKey", onSaveAsProject);
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
