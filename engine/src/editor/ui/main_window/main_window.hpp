//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <memory>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_internal.h"

// "" headers
#include "ui/common/view_model.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/go_hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/statusbar_component.hpp"
#include "ui/components/useful_obj_hierarchy_component.hpp"

#include <engine.hpp>
#include <gameplay/gui/window.hpp>
#include <management/components/transform/transform_component.hpp>
#include <management/ecs/core/ecs_types.hpp>
#include <management/ecs/ecs_coordinator.hpp>
#include <management/ecs/system/system.hpp>
#include <management/graphics/renderer.hpp>
#include <management/scene/scene.hpp>

namespace taixu::editor {

class MainWindow {
private:
    // names
    static std::string_view constexpr DOCK_SPACE_NAME{"TaixuEditorDock"};
    static std::string_view constexpr RENDER_COMPONENT_NAME{"Scene"};
    static std::string_view constexpr FILE_COMPONENT_NAME{"Files"};
    static std::string_view constexpr DETAILS_COMPONENT_NAME{
            "Components Details"};
    static std::string_view constexpr WORLD_OBJ_COMPONENT_NAME{"World Objects"};
    static std::string_view constexpr STATUS_COMPONENT_NAME{"Status"};
    static std::string_view constexpr USEFUL_OBJ_COMPONENT_NAME{
            "Useful Objects"};

    // components
    MenuComponent         menu_component{&_view_model};
    RenderComponent       render_component{&_view_model};
    GoHierarchyComponent  world_object_component{&_view_model};
    DetailComponent       detail_component{&_view_model};
    FileComponent         file_component{&_view_model};
    ConsoleComponent      status_component{&_view_model};
    UsefulObjectComponent useful_obj_component{&_view_model};
    StatusBarComponent    status_bar_component{&_view_model};

private:
    // context
    std::unique_ptr<Window> _window_ptr{nullptr};
    ViewModel               _view_model{};

private:
    /**
     * 一些const代码
     */
    static constexpr ImGuiWindowFlags DOCK_SPACE_FLAGS =
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
            ImGuiConfigFlags_NoMouseCursorChange |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

private:
    void buildUpUsefulObjHierarchy();
    void buildUpPathHierarchy();

public:
    explicit MainWindow(std::string const& title, int32_t width,
                        int32_t height);

    void init();
    void update();
    void destroy();

    void show();

private:
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

#endif// TAIXUENGINE_MAIN_WINDOW_HPP
