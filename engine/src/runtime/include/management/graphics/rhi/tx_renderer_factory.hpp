//
// Created by xmmmmmovo on 1/6/2024.
//

#ifndef ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC
#define ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC

#include "common/base/core.hpp"
#include "common/base/macro.hpp"
#include "common/designs/abstract_factory.hpp"
#include "common/designs/noncopyable.hpp"

#include "tx_scene_renderer.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

namespace taixu {

class SceneRendererFactory
    : private Noncopyable,
      public AbstractFactory<RenderAPI, AbstractSceneRenderer> {};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_MANAGEMENT_GRAPHICS_RHI_TX_RENDERER_FACTORY_DD07B240A7C841C8A00C4C34AD5907AC