//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>

#include <memory>

// "" headers
#include "graphics/renderer.hpp"
#include "gui/glfw_window.hpp"
#include "imgui_surface.hpp"

namespace taixu::editor {

class MainWindow : public gui::TX_GLFWwindow {
    using super = gui::TX_GLFWwindow;

private:
    std::unique_ptr<ImguiSurface> imgui_surface{};

public:
    MainWindow() : MainWindow(gui::IWindowContext{}) {}

    explicit MainWindow(gui::IWindowContext const &context)
        : gui::TX_GLFWwindow(context) {
        this->imgui_surface = std::make_unique<ImguiSurface>();
    };

    void init() override;
    void update() override;
    void destroy() override;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
