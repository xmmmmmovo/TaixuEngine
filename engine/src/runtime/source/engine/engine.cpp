#include "engine/engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "engine/engine_args.hpp"
#include <common/log/logger.hpp>

namespace taixu {

void Engine::preInit(std::vector<std::string> const& args) {
    Logger::init();
    _context.engine_args->initWithArgs(args);
}

void Engine::init(Window* window) { _context.init(window); }

void Engine::start() { _clock.reset(); }

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    _context.update(delta_time);
}

void Engine::destroy() { Logger::destroy(); }

}// namespace taixu