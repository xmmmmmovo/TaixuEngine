//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP
#define TAIXUENGINE_IMGUI_SURFACE_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "components/console_component.hpp"
#include "components/detail_component.hpp"
#include "components/file_component.hpp"
#include "components/hierarchy_component.hpp"
#include "components/menu_component.hpp"
#include "components/render_component.hpp"
#include "components/toolbar_component.hpp"

namespace taixu::editor {

/**
 * @brief Imgui render surface.
 */
class ImguiSurface {
private:
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
    std::shared_ptr<ApplicationContext> context{};

private:
    /**
     * @brief add widget to the surface
     * @param name the component name
     * @param update update function, most from component->update();
     * @param flags window flags
     * @see https://pixtur.github.io/mkdocs-for-imgui/site/api-imgui/Flags---Enumerations/
     * @see tests/benchmarks/function_transfer_benchmark.hpp
     * @param open open pointer, to judge whether window opened
     */
    template<class Func>
    void addWidget(char const *name, Func &&update,
                   ImGuiWindowFlags flags = 0, bool *open = nullptr);

public:
    ImguiSurface() {
        this->menu_component = std::make_unique<MenuComponent>();

        this->render_component       = std::make_unique<RenderComponent>();
        this->world_object_component = std::make_unique<HierarchyComponent>();
        this->detail_component       = std::make_unique<DetailComponent>();
        this->file_component         = std::make_unique<FileComponent>();
        this->status_component       = std::make_unique<ConsoleComponent>();
        this->useful_obj_component   = std::make_unique<HierarchyComponent>();
        this->tool_bar_component     = std::make_unique<ToolbarComponent>();

        this->context = Application::getInstance().getContext();
    }
    void Input_callback(std::string input);
    void Input_callback(glm::vec2 mouse_pos);
    void Input_callback(float scroll_yoffset);
    void init(GLFWwindow *window);

    void preUpdate();

    void update();

    void destroy();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
