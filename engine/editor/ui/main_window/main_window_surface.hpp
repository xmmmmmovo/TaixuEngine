//
// Created by xmmmmmovo on 2023/3/2.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP
#define TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP

#include "gui/imgui_surface.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/toolbar_component.hpp"

namespace taixu::editor {

class MainWindowSurface {
private:
    ImguiSurface imgui_surface{};

    // names
    static char constexpr DOCK_SPACE_NAME[]           = "TaixuEditorDock";
    static char constexpr RENDER_COMPONENT_NAME[]     = "Scene";
    static char constexpr FILE_COMPONENT_NAME[]       = "Files";
    static char constexpr DETAILS_COMPONENT_NAME[]    = "Components Details";
    static char constexpr WORLD_OBJ_COMPONENT_NAME[]  = "World Objects";
    static char constexpr STATUS_COMPONENT_NAME[]     = "Status";
    static char constexpr USEFUL_OBJ_COMPONENT_NAME[] = "Useful Objects";
    static char constexpr TOOLBAR_COMPONENT_NAME[]    = "Toolbar";

    // components
    std::unique_ptr<MenuComponent>      menu_component{};
    std::unique_ptr<RenderComponent>    render_component{};
    std::unique_ptr<HierarchyComponent> world_object_component{};
    std::unique_ptr<DetailComponent>    detail_component{};
    std::unique_ptr<FileComponent>      file_component{};
    std::unique_ptr<ConsoleComponent>   status_component{};
    std::unique_ptr<HierarchyComponent> useful_obj_component{};
    std::unique_ptr<ToolbarComponent>   tool_bar_component{};

    // context
    GLFWwindow     *parent_window{};
    IWindowContext *parent_context{};

public:
    MainWindowSurface() {
        this->menu_component = std::make_unique<MenuComponent>();

        this->render_component       = std::make_unique<RenderComponent>();
        this->world_object_component = std::make_unique<HierarchyComponent>();
        this->detail_component       = std::make_unique<DetailComponent>();
        this->file_component         = std::make_unique<FileComponent>();
        this->status_component       = std::make_unique<ConsoleComponent>();
        this->useful_obj_component   = std::make_unique<HierarchyComponent>();
        this->tool_bar_component     = std::make_unique<ToolbarComponent>();
    }

    void init(GLFWwindow *window);
    void preUpdate();
    void update();
    void destroy();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP
