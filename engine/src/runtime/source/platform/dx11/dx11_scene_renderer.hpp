//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1

#include "dx11_context.hpp"
#include "dx11_swapchain.hpp"
#include "management/graphics/rhi/tx_scene_renderer.hpp"

#include <wrl/client.h>

namespace taixu {

class DX11SceneRenderer final : public AbstractSceneRenderer {
private:
    template<typename T>
    using ComPtrT = Microsoft::WRL::ComPtr<T>;

private:
    ///
    /// 下面的变量都是为了present to screen准备的。
    ///

    DX11Context   _context;
    DX11SwapChain _swap_chain;

    ///
    /// 到这里为止
    ///

public:
    void init(Window* window) override;
    void update(float delta_time, Scene* scene) override;
    void destory() override;
    ~    DX11SceneRenderer() override;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
