//
// Created by xmmmmmovo on 1/7/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22

#include "gameplay/gui/window.hpp"
#include "management/graphics/gpu/shader_manager.hpp"
#include "scene.hpp"

namespace taixu {

class AbstractSceneRenderer : private Noncopyable {
protected:
    TXShaderModuleManager _shader_module_manager;

public:
    virtual void init(Window* window)                   = 0;
    virtual void update(float delta_time, Scene* scene) = 0;
    virtual void destroy()                              = 0;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_SCENE_RENDERER_0906B2209CBE4868A97BEE1FF83AFD22
