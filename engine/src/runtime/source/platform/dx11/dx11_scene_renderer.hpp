//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1

#include "dx11_buffer.hpp"
#include "dx11_shader.hpp"
#include "dx11_swapchain.hpp"
#include "management/scene/tx_scene_renderer.hpp"
#include "dx11_texture.hpp"

namespace taixu {

class DX11SceneRenderer final : public AbstractSceneRenderer {
private:
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
