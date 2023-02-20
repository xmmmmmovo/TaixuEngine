//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_MENU_COMPONENT_HPP
#define TAIXUENGINE_MENU_COMPONENT_HPP

#include <ImGuiFileDialog.h>

#include "core/application.hpp"
#include "interface/component.hpp"

namespace taixu::editor {

class MenuComponent : public IUIComponent {
private:
    std::shared_ptr<ApplicationContext> context{
            Application::getInstance().getContext()};

public:
    void init() override {}
    void update() override {
        if (ImGui::MenuItem("open project")) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    "ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
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
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName =
                        ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath =
                        ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MENU_COMPONENT_HPP
