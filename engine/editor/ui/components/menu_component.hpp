//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_MENU_COMPONENT_HPP
#define TAIXUENGINE_MENU_COMPONENT_HPP

#include <ImGuiFileDialog.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

#include "core/application.hpp"
#include "interface/component.hpp"

namespace taixu::editor {

class MenuComponent : public IUIComponent {
public:
    void init() override {}
    void update() override {
        if (ImGui::MenuItem("open project")) {
            // TODO: Just debug for this path, remove after decided
            ImGuiFileDialog::Instance()->OpenDialog(
                    "ChooseDirDlgKey", "Choose a Directory", nullptr,
                    "../tests", 1, nullptr, ImGuiFileDialogFlags_Modal);
        }
        if (ImGui::MenuItem("save project")) {}
        if (ImGui::MenuItem("save as project")) {}

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            Application::getInstance().destroy();
            exit(0);
        }
    }

    void processFileDialog() {
        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath =
                        ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                spdlog::debug(filePath);
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
