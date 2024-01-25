//
// Created by xmmmmmovo on 1/22/2024.
//

#include "engine/engine_context.hpp"

#include "management/graphics/rhi/tx_renderer_factory.hpp"
#include "management/graphics/rhi/tx_scene_renderer.hpp"

#include "management/scene/scene.hpp"
#include "resource/manager/asset_manager.hpp"

namespace taixu {

void EngineContext::init(Window* window) {
    renderer = SceneRendererFactory::createProduct(engine_args.render_api());
    renderer->init(window);

    asset_manager = std::make_shared<AssetManager>();
    scene         = std::make_shared<Scene>();
}

void EngineContext::destroy() const { renderer->destory(); }

}// namespace taixu