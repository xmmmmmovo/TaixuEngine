//
// Created by xmmmmmovo on 2023/2/13.
//

#ifndef TAIXUENGINE_IMGUI_SURFACE_HPP_0F8DE88846164C0CACACD00B10785DD4
#define TAIXUENGINE_IMGUI_SURFACE_HPP_0F8DE88846164C0CACACD00B10785DD4

#include "common/base/macro.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

namespace taixu::editor {

struct ImguiComponent {
    std::string_view      name{};
    std::function<void()> update_func{};
    ImGuiWindowFlags      flags{0};
    bool*                 open{nullptr};
};

/**
 * @brief Imgui render surface.
 * @details 现在只用于渲染editor部分
 */
class ImguiLayer {
private:
    ImGuiIO*    _io{nullptr};
    ImGuiStyle* _style{nullptr};

    std::vector<ImguiComponent> _components{};

    void loadCNFont() const;
    void loadStyle();

public:
    ImguiLayer();

    void init();
    void preUpdate();
    void update();
    void destroy();

    /**
     * @brief add widget to the surface
     * @param imgui_component imgui component add.
     * @see
     * https://pixtur.github.io/mkdocs-for-imgui/site/api-imgui/Flags---Enumerations/
     * @see tests/benchmarks/function_transfer_benchmark.hpp
     */
    void addComponents(const ImguiComponent& imgui_component);
};

}// namespace taixu::editor

#endif// TAIXUENGINE_IMGUI_SURFACE_HPP_0F8DE88846164C0CACACD00B10785DD4
