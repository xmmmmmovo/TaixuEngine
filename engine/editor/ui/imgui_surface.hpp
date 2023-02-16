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
    // components
    std::unique_ptr<RenderComponent>  renderComponent{};
    std::unique_ptr<ControlComponent> controlComponent{};
    std::unique_ptr<MenuComponent>    menuComponent{};

public:
    ImguiSurface() {
        this->renderComponent  = std::make_unique<RenderComponent>();
        this->controlComponent = std::make_unique<ControlComponent>();
        this->menuComponent    = std::make_unique<MenuComponent>();
    }

    void init(GLFWwindow *window);

    void pre_update();

    void update();

    void destroy();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
