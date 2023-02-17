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
#include "gui/glfw_window.hpp"
#include "imgui_surface.hpp"
#include"graphics/renderer.hpp"

namespace taixu::editor {

class MainWindow : public gui::TX_GLFWwindow {
    using super = gui::TX_GLFWwindow;

private:
    std::unique_ptr<ImguiSurface> imguiSurface{};

public:
    MainWindow() : MainWindow(gui::IWindowContext{}) {}

    explicit MainWindow(gui::IWindowContext const &context)
        : gui::TX_GLFWwindow(context) {
        this->imguiSurface     = std::make_unique<ImguiSurface>();
    };

    void init() override;
    void update() override;
    void destroy() override;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
