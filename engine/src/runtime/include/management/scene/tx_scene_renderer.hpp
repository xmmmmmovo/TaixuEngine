//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22

#include "common/base/macro.hpp"
#include "common/designs/noncopyable.hpp"
#include "common/math/color.hpp"
#include "management/gpu/shader_manager.hpp"

namespace taixu {

class Window;
class Scene;

enum class EnumImguiComponentType : std::uint8_t { WIDGET, MENUBAR };

struct ImguiComponent {
    using ImGuiComponentCallbackT = std::function<void()>;

    std::string_view        name{};
    EnumImguiComponentType  component_type{};
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

class AbstractSceneRenderer : private Noncopyable {
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(protected, bool, enable_imgui, true);

protected:
    TXShaderModuleManager _shader_module_manager;

    ///
    /// ImGui使用
    ///

    /**
     * @brief ImGui io接口
     **/
    ImGuiIO*    _io{nullptr};
    /**
     * @brief ImGui style
     */
    ImGuiStyle* _style{nullptr};

    /**
     * @brief ImGui component 集合
     */
    std::vector<ImguiComponent> _components{};

    /**
     * @brief 判断是否是editor模式
     */
    bool    _is_editor_mode{false};
    ImGuiID _dock_space_id{0};

    static constexpr ImGuiWindowFlags IMGUI_WINDOW_FLAG{
            ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground};
    static constexpr ImGuiDockNodeFlags IMGUI_DOCKSPACE_FLAGS{
            ImGuiDockNodeFlags_None ^ ImGuiDockNodeFlags_PassthruCentralNode};
    static constexpr std::string_view DOCK_SPACE_NAME{"TaixuEditorDock"};

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
