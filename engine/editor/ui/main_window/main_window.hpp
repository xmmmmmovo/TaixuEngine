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
#include "engine.hpp"
#include "gui/glfw_window.hpp"
#include "main_window_context.hpp"
#include "main_window_surface.hpp"

namespace taixu::editor {

class MainWindow : public TX_GLFWwindow, public IWindow {
    using super = TX_GLFWwindow;

    friend class MainWindowSurface;

private:
    std::unique_ptr<MainWindowSurface> main_imgui_surface{};
    std::shared_ptr<Renderer>          renderer{};

    // static raw engine runtime pointer
    // do not need to free
    Engine *engine_runtime{nullptr};

    // context
    MainWindowContext context{};

public:
    explicit MainWindow(MainWindowContext const &context);

    void init() override;
    void update() override;
    void destroy() override;

    void setEngineRuntime(Engine *engine_runtime_ptr);
    void init_imgui_surface();
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
