//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <memory>

#include "imgui.h"
#include "imgui_internal.h"

// "" headers
#include "gameplay/gui/window.hpp"
#include "ui/common/view_model.hpp"
#include "ui/components/console_component.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/go_hierarchy_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/statusbar_component.hpp"
#include "ui/components/useful_obj_hierarchy_component.hpp"

namespace taixu::editor {

class MainWindow {
private:
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
    ViewModel _view_model{};

    std::unique_ptr<Window> _window_ptr{nullptr};

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
    explicit MainWindow(WindowInfo&& window_info);

    void init();
    void update();
    void destroy() const;

    void start() const;

private:
    [[nodiscard]] inline bool isCursorInRenderComponent() const;
};

}// namespace taixu::editor

#endif// TAIXUENGINE_MAIN_WINDOW_HPP
