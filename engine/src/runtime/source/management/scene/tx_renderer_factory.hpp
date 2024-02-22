//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC

#include "common/base/core.hpp"
#include "common/designs/abstract_factory.hpp"
#include "common/designs/noncopyable.hpp"
#include "management/scene/tx_scene_renderer.hpp"

namespace taixu {

class SceneRendererFactory
    : private Noncopyable,
      public AbstractFactory<EnumRenderAPI, AbstractSceneRenderer> {};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC
