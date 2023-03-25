//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include "glad/glad.h"

#include <memory>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_internal.h"

// "" headers
#include "engine.hpp"
#include "gui/glfw_window.hpp"
#include "main_window_context.hpp"
#include "gui/imgui_surface.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/toolbar_component.hpp"


namespace taixu::editor {

class MainWindow : public TX_GLFWwindow, public IWindow {
    using super = TX_GLFWwindow;

private:
    std::shared_ptr<Renderer> renderer{};

    // static raw engine runtime pointer
    // do not need to free
    Engine* engine_runtime{nullptr};

    // context
    MainWindowContext context{};

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


public:
    explicit MainWindow(MainWindowContext const& context);

    void init() override;
    void update() override;
    void destroy() override;

    void setEngineRuntime(Engine* engine_runtime_ptr);
    void init_imgui_surface();

private:
    void preUpdate();

    // callback functions
    void onNewProjectCb(std::string_view const& path);
    void onOpenProjectCb(std::string_view const& path);
    void onSaveProjectCb();
    void onSaveAsProjectCb(std::string_view const& path);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
