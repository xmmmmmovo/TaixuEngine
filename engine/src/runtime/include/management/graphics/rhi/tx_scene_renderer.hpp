//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22

#include "common/base/macro.hpp"
#include "gameplay/gui/window.hpp"
#include "management/scene/scene.hpp"

namespace taixu {

class AbstractSceneRenderer : private Noncopyable {
public:
    virtual void init(Window* window)                   = 0;
    virtual void update(float delta_time, Scene* scene) = 0;

    virtual void onResize(int width, int height) = 0;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
