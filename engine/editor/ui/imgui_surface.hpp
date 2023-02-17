//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP
#define TAIXUENGINE_IMGUI_SURFACE_HPP

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "components/control_component.hpp"
#include "components/menu_component.hpp"
#include "components/render_component.hpp"

namespace taixu::editor {

class ImguiSurface {
private:
    // components
    std::unique_ptr<RenderComponent>  render_component{};
    std::unique_ptr<ControlComponent> control_component{};
    std::unique_ptr<MenuComponent>    menu_component{};

public:
    ImguiSurface() {
        this->render_component  = std::make_unique<RenderComponent>();
        this->control_component = std::make_unique<ControlComponent>();
        this->menu_component    = std::make_unique<MenuComponent>();
    }

    void init(GLFWwindow *window);

    void preUpdate();

    void update();

    void destroy();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
