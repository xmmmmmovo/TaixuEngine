//
// Created by xmmmmmovo on 1/7/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"
#include "common/math/color.hpp"
#include "gameplay/gui/window.hpp"
#include "management/gpu/shader_manager.hpp"
#include "management/render/tx_context.hpp"

#include "common/hal/tx_string.hpp"

namespace taixu {

class Scene;

enum class ImguiComponentType : std::uint8_t { WIDGET, MENUBAR };

struct ImGuiComponentInfo {
    using ImGuiComponentCallbackT = std::function<void()>;

    tx_string_view          name{};
    ImguiComponentType      component_type{};
    ImGuiComponentCallbackT update_func{nullptr};
    ImGuiComponentCallbackT end_call_back{nullptr};
    ImGuiWindowFlags        flags{0};
    bool*                   open{nullptr};
};

struct ImguiStyleGroup {
    Color background{0.0f, 0.0f, 0.0f, 0.0f};
    Color foreground{0.0f, 0.0f, 0.0f, 0.0f};
    Color text{0.0f, 0.0f, 0.0f, 0.0f};
    Color text_background{0.0f, 0.0f, 0.0f, 0.0f};
    Color highlight_primary{0.0f, 0.0f, 0.0f, 0.0f};
    Color hover_primary{0.0f, 0.0f, 0.0f, 0.0f};
    Color highlight_secondary{0.0f, 0.0f, 0.0f, 0.0f};
    Color hover_secondary{0.0f, 0.0f, 0.0f, 0.0f};
    Color modal_dim{0.0f, 0.0f, 0.0f, 0.0f};
};

class TXSceneRenderer final : public Noncopyable {
private:
    TXContext             _context;
    TXShaderModuleManager _shader_module_manager;

    ///
    /// ImGui使用的变量
    ///

    /**
     * @brief ImGui io接口
     **/
    ImGuiIO*    _io{nullptr};
    /**
     * @brief ImGui style
     */
    ImGuiStyle* _style{nullptr};

    std::function<void()> _imgui_update{nullptr};
    bool                  _enable_imgui{true};

public:
    void init(Window* window);
    void update(float delta_time, Scene* scene);
    void destroy();

    void enableImgui(const std::function<void()>& update_func);
    void disableImgui();

private:
    void        loadFont(DPIScale const& dpi_scale) const;
    void        loadStyle(DPIScale const& dpi_scale);
    static void initImguiForWindow(const Window* window);
    void        initImgui(const Window* window);
    void        imguiUpdate();
    void        imguiDestroy();

protected:
    void updateScene(float delta_time, Scene* scene);

    /**
     * @brief 初始化imgui API
     *
     */
    void imguiForGraphicsAPIInit();

    /**
     * @brief 初始化图形API
     *
     * @param window GLFW窗口
     */
    void initForGraphicsAPI(Window* window);

    void imguiGraphicsPreUpdate();
    void imguiGraphicsUpdate();
    void imguiGraphicsDestroy();

    void clearWindow();
    void presentToWindow();

    void destroyGraphicsAPI();
};

}// namespace taixu
