//
// Created by xmmmmmovo on 3/1/2024.
//

#include "menu_component.hpp"

#include "imgui/icons/IconsLucide.h"

namespace taixu::editor {

MenuComponent::MenuComponent(ViewModel* view_model)
    : AbstractUIComponent(view_model,
                          {.name           = MENU_KEY,
                           .component_type = EnumImguiComponentType::MENUBAR,
                           .update_func    = update,
                           .end_call_back  = endUpdate}) {
    registerCallback(EnumCallbacks::MENU_FILE_NEW_PROJECT,
                     Handler{+[](std::string const& file_path) {

                     }});
    registerCallback(EnumCallbacks::MENU_FILE_OPEN_PROJECT,
                     Handler{+[](std::string const& file_path) {}});
    registerCallback(EnumCallbacks::MENU_FILE_SAVE_PROJECT, Handler{+[] {}});
    registerCallback(EnumCallbacks::MENU_FILE_EXIT, Handler{+[] {}});
}

void MenuComponent::buildFileMenu() {
    if (ImGui::BeginMenu(FILE_MENU_KEY.data())) {
        static IGFD::FileDialogConfig const kconfig{
                .path              = getRootPath().generic_string(),
                .countSelectionMax = 1,
                .flags             = ImGuiFileDialogFlags_Modal};

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_FOLDER_PLUS, "New Project"))) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    FILE_NEW_PROJECT_DLG_KEY.data(), "Choose a Directory",
                    nullptr, kconfig);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_FOLDER_OPEN, "Open Project"))) {
            ImGuiFileDialog::Instance()->OpenDialog(
                    FILE_OPEN_PROJECT_DLG_KEY.data(), "Choose a Directory",
                    nullptr, kconfig);
        }

        if (enable) {
            if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_SAVE, "Save Project"))) {}
        }

        ImGui::Separator();

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_LOG_OUT, "Exit"))) {
            invokeCallback(EnumCallbacks::MENU_FILE_EXIT);
        }

        ImGui::EndMenu();
    }
}

void MenuComponent::buildEditMenu() {
    if (ImGui::BeginMenu(EDIT_MENU_KEY.data())) {

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_COPY, "Copy"))) {}

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_SCISSORS, "Cut"))) {}

        ImGui::EndMenu();
    }
}

void MenuComponent::buildWindowMenu() {
    if (ImGui::BeginMenu(WINDOW_MENU_KEY.data())) {
        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_X_SQUARE, "Close"))) {}

        ImGui::EndMenu();
    }
}

void MenuComponent::buildHelpMenu() {
    if (ImGui::BeginMenu(HELP_MENU_KEY.data())) {
        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_INFO, "About"))) {}
        ImGui::EndMenu();
    }
}

void MenuComponent::update() {
    buildFileMenu();
    if (enable) {
        buildEditMenu();
        buildWindowMenu();
        buildHelpMenu();
    }
}

void MenuComponent::endUpdate() {
    // display
    onDialogOpen(FILE_NEW_PROJECT_DLG_KEY,
                 EnumCallbacks::MENU_FILE_NEW_PROJECT);
    onDialogOpen(FILE_OPEN_PROJECT_DLG_KEY,
                 EnumCallbacks::MENU_FILE_OPEN_PROJECT);
}

void MenuComponent::onDialogOpen(const std::string_view& key,
                                 const EnumCallbacks     enum_callback) {
    if (ImGuiFileDialog::Instance()->Display(key.data())) {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string const file_path =
                    ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            DEBUG_LOG(file_path);
            invokeCallback(enum_callback, file_path);
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}

}// namespace taixu::editor