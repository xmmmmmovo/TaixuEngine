//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP
#define TAIXUENGINE_IMGUI_SURFACE_HPP

#include "GLFW/glfw3.h"

namespace taixu::gui {

class ImguiSurface {

public:
    void init(GLFWwindow *window);

    void pre_update();

    void update();

    void destroy();
};

}// namespace taixu::gui

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
