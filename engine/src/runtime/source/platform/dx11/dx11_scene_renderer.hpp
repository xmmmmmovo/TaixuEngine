//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1

#include "common/math/vec.hpp"
#include "dx11_buffer.hpp"
#include "dx11_context.hpp"
#include "dx11_shader.hpp"
#include "dx11_swapchain.hpp"
#include "management/scene/tx_scene_renderer.hpp"

namespace taixu {

struct V {
    Vec3 pos;
    Vec4 color;
};

class DX11SceneRenderer final : public AbstractSceneRenderer {
private:
    ///
    /// 下面的变量都是为了present to screen准备的。
    ///

    DX11Context   _context;
    DX11SwapChain _swap_chain;

    ///
    /// 到这里为止
    ///

    // test
    std::shared_ptr<DX11ShaderModule<ID3D11VertexShader>> vert;
    std::shared_ptr<DX11ShaderModule<ID3D11PixelShader>>  frag;
    std::shared_ptr<DX11Buffer>                           buffer;

public:
    ~    DX11SceneRenderer() override;
    void updateScene(float delta_time, Scene* scene) override;

protected:
    void imguiForGraphicsAPIInit() override;
    void imguiGraphicsPreUpdate() override;
    void imguiGraphicsUpdate() override;
    void imguiGraphicsDestroy() override;

    void clearWindow() override;
    void presentToWindow() override;

    void initForGraphicsAPI(Window* window) override;
    void destroyGraphicsAPI() override;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
