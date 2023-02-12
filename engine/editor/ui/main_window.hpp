//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_MAIN_WINDOW_HPP
#define TAIXUENGINE_MAIN_WINDOW_HPP

#include <imgui.h>
#include <imgui_internal.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "components/control_component.hpp"
#include "components/render_component.hpp"
#include "gui/window.hpp"

namespace taixu::editor {

class MainWindow : public interface::IWindow {
public:
    void init() override;
    void render() override;
    ~MainWindow() override;

private:
    GLFWwindow *window{nullptr};

    // components
    std::unique_ptr<RenderComponent>  renderComponent{nullptr};
    std::unique_ptr<ControlComponent> controlComponent{nullptr};

public:
    MainWindow() = default;
    MainWindow(std::int32_t const &width, std::int32_t const &height,
               std::string_view const &title)
        : interface::IWindow(width, height, title) {}
};

}// namespace taixu::editor

#endif//TAIXUENGINE_MAIN_WINDOW_HPP
