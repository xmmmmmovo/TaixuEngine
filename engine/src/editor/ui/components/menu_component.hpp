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

#include "common/log/logger.hpp"

namespace taixu::editor {

/**
 * @brief 菜单栏组件
 */
class MenuComponent final : public AbstractUIComponent {
private:
    static constexpr std::string_view MENU_KEY        = "Menu";
    static constexpr std::string_view FILE_MENU_KEY   = "File";
    static constexpr std::string_view EDIT_MENU_KEY   = "Edit";
    static constexpr std::string_view WINDOW_MENU_KEY = "Window";
    static constexpr std::string_view HELP_MENU_KEY   = "Help";

    static constexpr std::string_view FILE_NEW_PROJECT_DLG_KEY =
            "file_new_project";
    static constexpr std::string_view FILE_OPEN_PROJECT_DLG_KEY =
            "file_open_project";

public:
    explicit MenuComponent(ViewModel* view_model);

private:
    static void buildFileMenu();
    static void buildEditMenu();
    static void buildWindowMenu();
    static void buildHelpMenu();

    static void update();
    static void endUpdate();

    static void onDialogOpen(std::string_view const& key,
                             EnumCallbacks           enum_callback);
};

}// namespace taixu::editor

#endif// ENGINE_EDITOR_UI_COMPONENTS_MENU_COMPONENT
