//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1

#include "management/graphics/rhi/tx_scene_renderer.hpp"

#include <wrl/client.h>

#include "platform/os/windows/windows_min.hpp"
#include <d3d11_1.h>

namespace taixu {

class DX11SceneRenderer : public AbstractSceneRenderer {
private:
    template<typename T>
    using ComPtrT = Microsoft::WRL::ComPtr<T>;

public:
    void init() override;
    void update(float delta_time, Scene* scene) override;

    ~DX11SceneRenderer() override;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_SCENE_RENDERER_499239DA41144D1D9535ADB888492EF1
