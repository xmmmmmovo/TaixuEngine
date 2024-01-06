//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_RENDERER_8E34BCE0BEE841BAB25EA79949940B77
#define ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_RENDERER_8E34BCE0BEE841BAB25EA79949940B77

#include "management/graphics/rhi/tx_renderer.hpp"

namespace taixu {

class DX11Renderer : public IRenderer {
public:
    void init() override;
    void update(float delta_time) override;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_PLATFORM_DX11_DX11_RENDERER_8E34BCE0BEE841BAB25EA79949940B77
