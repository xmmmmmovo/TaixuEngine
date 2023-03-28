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
#include "gui/imgui_surface.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/statusbar_component.hpp"

namespace taixu::editor {

class MainWindow : public IWindow {
private:
    // names
    static char constexpr DOCK_SPACE_NAME[]           = "TaixuEditorDock";
    static char constexpr RENDER_COMPONENT_NAME[]     = "Scene";
    static char constexpr FILE_COMPONENT_NAME[]       = "Files";
    static char constexpr DETAILS_COMPONENT_NAME[]    = "Components Details";
    static char constexpr WORLD_OBJ_COMPONENT_NAME[]  = "World Objects";
    static char constexpr STATUS_COMPONENT_NAME[]     = "Status";
    static char constexpr USEFUL_OBJ_COMPONENT_NAME[] = "Useful Objects";

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
    std::unique_ptr<StatusBarComponent> status_bar_component{
            std::make_unique<StatusBarComponent>()};


private:
    std::shared_ptr<Renderer> renderer{};

    // static raw engine runtime pointer
    // do not need to free
    Engine* engine_runtime{nullptr};

    // context
    std::shared_ptr<WindowContext> context_ptr{};

    ImVec2 _mouse_pos{0.0f, 0.0f};

public:
    explicit MainWindow(std::shared_ptr<WindowContext> const& context_ptr);

    void init() override;
    void update() override;
    void destroy() override;

    void setEngineRuntime(Engine* engine_runtime_ptr);

private:
    inline void showRenderComponent() const;

    void preUpdate();

    [[nodiscard]] inline bool isCursorInRenderComponent() const;

private:
    // callback functions
    void onNewProjectCb(std::string_view const& path);
    void onOpenProjectCb(std::string_view const& path);
    void onSaveProjectCb();
    void onSaveAsProjectCb(std::string_view const& path);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
