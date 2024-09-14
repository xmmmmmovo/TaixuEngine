//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <memory>

#include "imgui.h"
#include "imgui_internal.h"

// "" headers
#include <taixu/gameplay/gui/window.hpp>

#include "ui/common/view_model.hpp"
#include "ui/components/detail_component.hpp"
#include "ui/components/file_component.hpp"
#include "ui/components/menu_component.hpp"
#include "ui/components/render_component.hpp"
#include "ui/components/scene_graph_component.hpp"
#include "ui/components/useful_obj_hierarchy_component.hpp"

namespace taixu::editor {

class MainWindow {
private:
    static constexpr std::string_view STARTUP_OPEN_PROJECT_DLG_KEY = "startup_open_project_file_dlg";

private:
    ViewModel _view_model{};

    // components
    MenuComponent         _menu_component{_view_model};
    RenderComponent       _render_component{_view_model};
    SceneGraphComponent   _scene_graph_component{_view_model};
    DetailComponent       _detail_component{_view_model};
    FileComponent         _file_component{_view_model};
    UsefulObjectComponent _useful_obj_component{_view_model};

private:
    std::unique_ptr<Window> _window_ptr{nullptr};

private:
    /**
     * window相关flag
     */
    static constexpr ImGuiWindowFlags IMGUI_WINDOW_FLAG{
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground};
    /**
     * DockSpace相关flag
     */
    static constexpr ImGuiDockNodeFlags IMGUI_DOCKSPACE_FLAGS{ImGuiDockNodeFlags_None ^
                                                              ImGuiDockNodeFlags_PassthruCentralNode};

    static constexpr std::string_view VIEW_HOLDER_NAME{"#TaixuEditorViewHolder"};
    static constexpr std::string_view DOCK_SPACE_NAME{"TaixuEditorDock"};

    ImGuiID _dock_space_id{0};

private:
    void buildUpPathHierarchy();

public:
    explicit MainWindow(WindowInfo&& window_info);

    void init();
    void update();
    void imguiUpdate();
    void destroy() const;

    void start() const;

private:
    [[nodiscard]] inline bool isCursorInRenderComponent() const;
};

}// namespace taixu::editor

#endif// TAIXUENGINE_MAIN_WINDOW_HPP
