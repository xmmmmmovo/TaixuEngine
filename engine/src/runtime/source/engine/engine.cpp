#include "engine/engine.hpp"

#include "common/log/logger.hpp"
#include "engine/engine_context.hpp"
#include "management/scene/tx_scene_renderer.hpp"

namespace taixu {

void Engine::preInit() { Logger::init(); }

void Engine::init(std::vector<std::string> const& args, Window* window) {
    g_engine_context.init(args, window);
}

void Engine::beforeStart() { _clock.reset(); }

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    g_engine_context.renderer->update(delta_time, nullptr);
}

void Engine::destroy() { Logger::destroy(); }

}// namespace taixu