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

namespace taixu::editor {

class MainWindow : public gui::TX_GLFWwindow {
public:
    ~MainWindow() override;

private:
    // components
    std::unique_ptr<RenderComponent>  renderComponent{nullptr};
    std::unique_ptr<ControlComponent> controlComponent{nullptr};

public:
    MainWindow() = default;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
