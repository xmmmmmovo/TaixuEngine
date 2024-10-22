//
// Created by xmmmmmovo on 3/1/2024.
//

#include "menu_component.hpp"

#include "imgui/file_dialog/ImGuiFileDialog.h"
#include "imgui/icons/IconsLucide.h"
#include "ui/common/dialog_helper.hpp"

namespace taixu::editor {

static constexpr std::string_view FILE_MENU_KEY   = "File";
static constexpr std::string_view EDIT_MENU_KEY   = "Edit";
static constexpr std::string_view WINDOW_MENU_KEY = "Window";
static constexpr std::string_view HELP_MENU_KEY   = "Help";

static constexpr std::string_view FILE_NEW_PROJECT_DLG_KEY  = "file_new_project";
static constexpr std::string_view FILE_OPEN_PROJECT_DLG_KEY = "file_open_project";

MenuComponent::MenuComponent(ViewModel& view_model) : AbstractUIComponent(view_model) {
    registerCallback(Callbacks::MENU_FILE_NEW_PROJECT, Handler{+[](std::string const& file_path) {}});
    registerCallback(Callbacks::MENU_FILE_SAVE_PROJECT, Handler{+[] {}});
    registerCallback(Callbacks::MENU_FILE_EXIT, Handler{+[] {}});
}

void MenuComponent::buildFileMenu() {
    if (ImGui::BeginMenu(FILE_MENU_KEY.data())) {

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_FOLDER_PLUS, "New Project"))) {
            openFileDialog(FILE_NEW_PROJECT_DLG_KEY.data(), DIRECTORY_CONFIG);
        }

        ImGui::Separator();

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_FOLDER_OPEN, "Open Project"))) {
            openFileDialog(FILE_OPEN_PROJECT_DLG_KEY.data(), DIRECTORY_CONFIG);
        }

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_SAVE, "Save Project"))) {}

        ImGui::Separator();

        if (ImGui::MenuItem(ICON_ENTRY(ICON_LC_LOG_OUT, "Exit"))) {
            invokeCallback(Callbacks::MENU_FILE_EXIT);
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

void MenuComponent::update() const {
    if (ImGui::BeginMenuBar()) {
        buildFileMenu();
        buildEditMenu();
        buildWindowMenu();
        buildHelpMenu();
        ImGui::EndMenuBar();
    }
    endUpdate();
}

void MenuComponent::endUpdate() const {
    // display
    displayAndProcessFileDialog(FILE_NEW_PROJECT_DLG_KEY, _view_model, Callbacks::MENU_FILE_NEW_PROJECT);
    displayAndProcessFileDialog(FILE_OPEN_PROJECT_DLG_KEY, _view_model, Callbacks::FILE_OPEN_PROJECT);
}

}// namespace taixu::editor
