//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_GLFW_WINDOW_HPP
#define TAIXUENGINE_GLFW_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

// "" headers
#include "window.hpp"
#include "window_prop.hpp"

namespace taixu::gui {

class TX_GLFWwindow : IWindow {
public:
    TX_GLFWwindow();

private:
    void init() override;
    void render() override;
    void destroy() override;

private:
    GLFWwindow *window{nullptr};
    IWindowProp prop{};
};

}// namespace taixu::gui

#endif//TAIXUENGINE_GLFW_WINDOW_HPP
