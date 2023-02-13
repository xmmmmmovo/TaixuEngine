//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <memory>

#include <imgui.h>
#include <imgui_internal.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// "" headers
#include "components/control_component.hpp"
#include "components/render_component.hpp"
#include "gui/glfw_window.hpp"
#include "gui/surface/imgui_surface.hpp"

namespace taixu::editor {

class MainWindow : public gui::TX_GLFWwindow {
    using super = gui::TX_GLFWwindow;

private:
    // components
    std::unique_ptr<RenderComponent>   renderComponent{};
    std::unique_ptr<ControlComponent>  controlComponent{};
    std::unique_ptr<gui::ImguiSurface> imguiSurface{};

public:
    MainWindow() : MainWindow(gui::IWindowContext{}) {}

    explicit MainWindow(gui::IWindowContext const &context)
        : gui::TX_GLFWwindow(context) {
        this->imguiSurface     = std::make_unique<gui::ImguiSurface>();
        this->renderComponent  = std::make_unique<RenderComponent>();
        this->controlComponent = std::make_unique<ControlComponent>();
    };

    void init() override;
    void update() override;
    void destroy() override;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
