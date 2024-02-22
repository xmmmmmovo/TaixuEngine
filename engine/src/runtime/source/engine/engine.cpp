#include "engine/engine.hpp"

#include "common/log/logger.hpp"
#include "management/graphics/rhi/tx_renderer_factory.hpp"
#include "management/scene/tx_scene_renderer.hpp"

#include "management/scene/scene.hpp"
#include "resource/manager/asset_manager.hpp"

namespace taixu {

Engine g_engine;

void Engine::init(std::vector<std::string> const& args, Window* window) {
    Logger::init();

    _engine_args.initWithArgs(args);

    this->window = window;

    renderer = SceneRendererFactory::createProduct(_engine_args.render_api());
    renderer->init(window);

    asset_manager = std::make_shared<AssetManager>();
    scene         = std::make_shared<Scene>();
}

void Engine::beforeStart() { _clock.reset(); }

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    renderer->update(delta_time, nullptr);
}

void Engine::destroy() {
    renderer->destroy();
    Logger::destroy();
}

EngineArgs const& Engine::getArgs() { return _engine_args; }

void Engine::changeEngineState(EnumEngineState state) { _state = state; }

}// namespace taixu