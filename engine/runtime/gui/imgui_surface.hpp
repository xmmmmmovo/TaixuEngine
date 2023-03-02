//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP
#define TAIXUENGINE_IMGUI_SURFACE_HPP

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace taixu::editor {

/**
 * @brief Imgui render surface.
 * @details 现在只用于渲染editor部分
 */
class ImguiSurface {
public:
    ImguiSurface() = default;

    void init(GLFWwindow *window);

    void preUpdate();

    void update();

    void destroy();

    /**
     * @brief add widget to the surface
     * @param name the component name
     * @param update update function, most from component->update();
     * @param flags window flags
     * @see https://pixtur.github.io/mkdocs-for-imgui/site/api-imgui/Flags---Enumerations/
     * @see tests/benchmarks/function_transfer_benchmark.hpp
     * @param open open pointer, to judge whether window opened
     */
    void addWidget(char const *name, std::function<void()> const &update,
                   ImGuiWindowFlags flags = 0, bool *open = nullptr);
};

}// namespace taixu::editor

#endif//TAIXUENGINE_IMGUI_SURFACE_HPP
