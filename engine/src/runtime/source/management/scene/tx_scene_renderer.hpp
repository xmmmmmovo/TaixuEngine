//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22

#include "common/math/color.hpp"
#include "gameplay/gui/window.hpp"
#include "management/graphics/gpu/shader_manager.hpp"
#include "scene.hpp"

#define IMGUI_ENABLE_FREETYPE
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

namespace taixu {

struct ImguiComponent {
    std::string_view      name{};
    std::function<void()> update_func{};
    ImGuiWindowFlags      flags{0};
    bool*                 open{nullptr};
};

struct ImguiStyleGroup {
    Color background;
    Color foreground;
    Color text;
    Color text_background;
    Color highlight_primary;
    Color hover_primary;
    Color highlight_secondary;
    Color hover_secondary;
    Color modal_dim;
};

class AbstractSceneRenderer : private Noncopyable {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, bool, enable_imgui, true);

protected:
    TXShaderModuleManager _shader_module_manager;

    ImGuiIO*    _io{nullptr};
    ImGuiStyle* _style{nullptr};

    std::vector<ImguiComponent> _components{};

    bool is_editor_mode{false};

public:
    void init(Window* window);
    void update(float delta_time, Scene* scene);
    void destroy();

private:
    void        loadFont() const;
    void        loadStyle();
    static void initImguiForWindow(const Window* window);
    void        initImgui(const Window* window);
    void        imguiUpdate();
    void        imguiDestroy();

protected:
    virtual void updateScene(float delta_time, Scene* scene) = 0;
    /**
     * @brief 这里因为要适配不同的API所以是虚函数
     */
    virtual void imguiForGraphicsAPIInit()                   = 0;
    virtual void initForGraphicsAPI(Window* window)          = 0;

    virtual void imguiGraphicsPreUpdate() = 0;
    virtual void imguiGraphicsUpdate()    = 0;
    virtual void imguiGraphicsDestroy()   = 0;

    virtual void clearWindow()     = 0;
    virtual void presentToWindow() = 0;

    virtual void destroyGraphicsAPI() = 0;

public:
    /**
     * @brief add widget to the surface
     * @param imgui_component imgui component add.
     * @see
     * https://pixtur.github.io/mkdocs-for-imgui/site/api-imgui/Flags---Enumerations/
     * @see tests/benchmarks/function_transfer_benchmark.hpp
     */
    void addComponent(const ImguiComponent& imgui_component);
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
