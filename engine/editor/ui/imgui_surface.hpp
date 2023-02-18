//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP
#define TAIXUENGINE_IMGUI_SURFACE_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "components/control_component.hpp"
#include "components/menu_component.hpp"
#include "components/render_component.hpp"

namespace taixu::editor {

class ImguiSurface {
private:
    // names
    static char constexpr DOCK_SPACE_NAME[]          = "TaixuEditorDock";
    static char constexpr RENDER_COMPONENT_NAME[]    = "Scene";
    static char constexpr FILE_COMPONENT_NAME[]      = "Files";
    static char constexpr DETAILS_COMPONENT_NAME[]   = "Components Details";
    static char constexpr WORLD_OBJ_COMPONENT_NAME[] = "Components Details";

    // components
    std::unique_ptr<RenderComponent>      render_component{};
    std::unique_ptr<WorldObjectComponent> world_object_component{};
    std::unique_ptr<MenuComponent>        menu_component{};

public:
    ImguiSurface() {
        this->render_component = std::make_unique<RenderComponent>();
        this->render_component->setName(RENDER_COMPONENT_NAME);
        this->world_object_component = std::make_unique<WorldObjectComponent>();
        this->world_object_component->setName(WORLD_OBJ_COMPONENT_NAME);
        this->menu_component = std::make_unique<MenuComponent>();
    }

    void init(GLFWwindow *window);

    void preUpdate();

    void update();

    void destroy();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
