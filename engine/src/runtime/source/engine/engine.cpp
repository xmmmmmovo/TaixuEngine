#include "engine/engine.hpp"

#include "common/log/logger.hpp"
#include "engine/engine_context.hpp"
#include "management/graphics/rhi/tx_scene_renderer.hpp"

namespace taixu {

void Engine::preInit(std::vector<std::string> const& args) {
    Logger::init();
    _context.engine_args.initWithArgs(args);
}

void Engine::init(Window* window) { _context.init(window); }

void Engine::beforeStart() { _clock.reset(); }

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    _context.renderer->update(delta_time, nullptr);
}

void Engine::destroy() { Logger::destroy(); }

EngineContext* Engine::getContext() { return &_context; }

}// namespace taixu