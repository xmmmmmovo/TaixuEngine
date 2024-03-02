#include "engine/engine.hpp"

#include "common/log/logger.hpp"
#include "management/scene/tx_renderer_factory.hpp"
#include "management/scene/tx_scene_renderer.hpp"

#include "management/scene/scene.hpp"
#include "resource/manager/asset_manager.hpp"

namespace taixu {

Engine g_engine;

void Engine::initRuntime(std::vector<std::string> const& args) {
    Logger::init();
    INFO_LOG("Logger inited, start init engine");
    _engine_args.initWithArgs(args);
}

void Engine::initWithWindow(Window* window) {
    this->_window = window;

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

void Engine::destroy() const {
    renderer->destroy();
    Logger::destroy();
}

EngineArgs const& Engine::getArgs() { return _engine_args; }

void Engine::changeEngineState(const EnumEngineState state) { _state = state; }

bool Engine::loadProject(std::filesystem::path const& path) {
    return false;
}

}// namespace taixu