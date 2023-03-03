//
// Created by xmmmmmovo on 2023/3/2.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP
#define TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP

#include "gui/imgui_surface.hpp"
#include "main_window_context.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/toolbar_component.hpp"


namespace taixu::editor {

class MainWindow;

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
    std::unique_ptr<MenuComponent> menu_component{
            std::make_unique<MenuComponent>()};
    std::unique_ptr<RenderComponent> render_component{
            std::make_unique<RenderComponent>()};
    std::unique_ptr<HierarchyComponent> world_object_component{
            std::make_unique<HierarchyComponent>()};
    std::unique_ptr<DetailComponent> detail_component{
            std::make_unique<DetailComponent>()};
    std::unique_ptr<FileComponent> file_component{
            std::make_unique<FileComponent>()};
    std::unique_ptr<ConsoleComponent> status_component{
            std::make_unique<ConsoleComponent>()};
    std::unique_ptr<HierarchyComponent> useful_obj_component{
            std::make_unique<HierarchyComponent>()};
    std::unique_ptr<ToolbarComponent> tool_bar_component{
            std::make_unique<ToolbarComponent>()};

    // context
    MainWindow* parent_window{};

public:
    explicit MainWindowSurface(MainWindow* parent_window) {
        this->parent_window = parent_window;

        this->menu_component->bindCallbacks(
                INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onNewProjectCb),
                INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onOpenProjectCb),
                INCLASS_VOID_FUNCTION_LAMBDA_WRAPPER(onSaveProjectCb),
                INCLASS_STR_FUNCTION_LAMBDA_WRAPPER(onSaveAsProjectCb));
    }

    void init();
    void preUpdate();
    void update();
    void destroy();

private:
    // callback functions

    void onNewProjectCb(std::string_view const& path);
    void onOpenProjectCb(std::string_view const& path);
    void onSaveProjectCb();
    void onSaveAsProjectCb(std::string_view const& path);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_SURFACE_HPP
