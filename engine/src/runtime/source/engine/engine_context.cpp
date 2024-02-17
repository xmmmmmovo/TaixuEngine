//
// Created by xmmmmmovo on 1/22/2024.
//

#include "engine/engine_context.hpp"

#include "management/graphics/rhi/tx_renderer_factory.hpp"
#include "management/scene/tx_scene_renderer.hpp"

#include "management/scene/scene.hpp"
#include "resource/manager/asset_manager.hpp"

namespace taixu {

EngineContext g_engine_context;

void EngineContext::init(std::vector<std::string> const& args, Window* window) {
    engine_args.initWithArgs(args);

    this->window = window;

    renderer = SceneRendererFactory::createProduct(engine_args.render_api());
    renderer->init(window);

    asset_manager = std::make_shared<AssetManager>();
    scene         = std::make_shared<Scene>();
}

void EngineContext::destroy() const { renderer->destroy(); }

}// namespace taixu