//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include "glad/glad.h"

#include <memory>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_internal.h"

// "" headers
#include "graphics/renderer.hpp"
#include "gui/glfw_window.hpp"
#include "ui/imgui_surface.hpp"

namespace taixu::editor {

class MainWindow : public TX_GLFWwindow {
    using super = TX_GLFWwindow;

private:
    std::unique_ptr<ImguiSurface> imgui_surface{};

private:
    void bindCallbacks();

public:
    MainWindow() : MainWindow(IWindowContext{}) {}

    explicit MainWindow(IWindowContext const &context)
        : TX_GLFWwindow(context) {
        this->imgui_surface = std::make_unique<ImguiSurface>();
    };

    void init() override;
    void update() override;
    void destroy() override;
    void processInput(GLFWwindow *window);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
